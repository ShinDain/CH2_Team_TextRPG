#include "pch.h"
#include "State_Map.h"
#include "Combat/BattleStartData.h"
#include "Core/GameProgress.h"
#include "Data/Character/Stat.h"
#include "Data/JsonDataParser.h"
#include "Data/Table/MonsterDataTable.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleUtil.h"
#include "UI/GameScreen.h"
#include "Character/Player/Player.h" 

#include <filesystem>
#include <random>
#include <windows.h>

#include "Manager/ObjectManager.h"
#include "Manager/UserSaveManager.h"

namespace
{
struct MapEncounter
{
	uint32_t MonsterId = 0;
	int Count = 0;
};

bool IsBattleNode(ENodeType Type)
{
	return Type == ENodeType::Monster ||
		Type == ENodeType::Elite ||
		Type == ENodeType::Boss;
}

std::filesystem::path GetExecutableDirectory()
{
	char ModulePath[MAX_PATH] = {};
	const DWORD Length = GetModuleFileNameA(nullptr, ModulePath, MAX_PATH);

	if (Length == 0 || Length == MAX_PATH)
	{
		return {};
	}

	return std::filesystem::path(ModulePath).parent_path();
}

void AddScriptPathCandidates(
	std::vector<std::filesystem::path>& Candidates,
	const std::filesystem::path& BasePath,
	const std::filesystem::path& RelativePath
)
{
	if (BasePath.empty())
	{
		return;
	}

	Candidates.push_back(BasePath / RelativePath);

	if (BasePath.has_parent_path())
	{
		Candidates.push_back(BasePath.parent_path() / RelativePath);
	}

	if (BasePath.has_parent_path() && BasePath.parent_path().has_parent_path())
	{
		Candidates.push_back(BasePath.parent_path().parent_path() / RelativePath);
	}
}

std::vector<std::filesystem::path> MakeScriptPathCandidates(const std::filesystem::path& RelativePath)
{
	std::vector<std::filesystem::path> Candidates;

	AddScriptPathCandidates(Candidates, std::filesystem::current_path(), RelativePath);
	AddScriptPathCandidates(Candidates, GetExecutableDirectory(), RelativePath);

	return Candidates;
}

bool LoadJsonFromCandidates(const std::vector<std::filesystem::path>& Candidates, json& OutJson)
{
	for (const std::filesystem::path& Candidate : Candidates)
	{
		if (!std::filesystem::exists(Candidate))
		{
			continue;
		}

		if (JsonDataParser::Load(Candidate.string(), OutJson))
		{
			return true;
		}
	}

	return false;
}

bool LoadMapEncountersForFloor(int Floor, std::vector<MapEncounter>& OutEncounters, LogManager& Log)
{
	json MapJson;

	if (!LoadJsonFromCandidates(
		MakeScriptPathCandidates(std::filesystem::path("Script") / "Map" / "MapData_1.json"),
		MapJson) ||
		!MapJson.is_array())
	{
		Log.AddLog("맵 전투 데이터를 찾을 수 없습니다.");
		return false;
	}

	for (const json& FloorData : MapJson)
	{
		if (!FloorData.contains("Floor") || FloorData["Floor"].get<int>() != Floor)
		{
			continue;
		}

		if (!FloorData.contains("Encounters") || !FloorData["Encounters"].is_array())
		{
			Log.AddLog("현재 층의 전투 데이터가 올바르지 않습니다.");
			return false;
		}

		for (const json& EncounterData : FloorData["Encounters"])
		{
			if (!EncounterData.contains("Id") || !EncounterData.contains("Count"))
			{
				continue;
			}

			MapEncounter Encounter;
			Encounter.MonsterId = EncounterData["Id"].get<uint32_t>();
			Encounter.Count = EncounterData["Count"].get<int>();

			if (Encounter.Count > 0)
			{
				OutEncounters.push_back(Encounter);
			}
		}

		return !OutEncounters.empty();
	}

	Log.AddLog("현재 층의 전투 후보가 없습니다.");
	return false;
}

bool TryFindMonsterStartData(uint32_t MonsterId, BattleMonsterStartData& OutMonster)
{
	const MonsterData* Monster = MonsterDataTable::GetInstance().FindMonsterDataById(MonsterId);

	if (Monster != nullptr)
	{
		OutMonster.MonsterId = Monster->Id;
		OutMonster.Name = Monster->Name;
		OutMonster.HP = static_cast<int>(Monster->HP);
		OutMonster.Attack = static_cast<int>(Monster->Attack);
		OutMonster.Defense = static_cast<int>(Monster->Defense);
		OutMonster.Type = Monster->Type;
		return true;
	}

	json MonsterJson;

	if (!LoadJsonFromCandidates(
		MakeScriptPathCandidates(std::filesystem::path("Script") / "Monster" / "MonsterData.json"),
		MonsterJson) ||
		!MonsterJson.is_array())
	{
		return false;
	}

	for (const json& MonsterDataJson : MonsterJson)
	{
		if (!MonsterDataJson.contains("Id") ||
			!MonsterDataJson.contains("Name") ||
			!MonsterDataJson.contains("Type") ||
			!MonsterDataJson.contains("HP") ||
			!MonsterDataJson.contains("Attack") ||
			!MonsterDataJson.contains("Defense"))
		{
			continue;
		}

		if (MonsterDataJson["Id"].get<uint32_t>() == MonsterId)
		{
			OutMonster.MonsterId = MonsterId;
			OutMonster.Name = MonsterDataJson["Name"].get<std::string>();
			OutMonster.HP = MonsterDataJson["HP"].get<int>();
			OutMonster.Attack = MonsterDataJson["Attack"].get<int>();
			OutMonster.Defense = MonsterDataJson["Defense"].get<int>();
			OutMonster.Type = MonsterDataJson["Type"].get<std::string>();
			return true;
		}
	}

	return false;
}

bool TrySelectEncounterForFloor(int Floor, MapEncounter& OutEncounter, LogManager& Log)
{
	std::vector<MapEncounter> Encounters;

	if (!LoadMapEncountersForFloor(Floor, Encounters, Log))
	{
		return false;
	}

	std::vector<MapEncounter> ValidEncounters;

	for (const MapEncounter& Encounter : Encounters)
	{
		BattleMonsterStartData Monster;

		if (!TryFindMonsterStartData(Encounter.MonsterId, Monster))
		{
			Log.AddLog("몬스터 데이터를 찾을 수 없습니다. Id: " + std::to_string(Encounter.MonsterId));
			continue;
		}

		if (Monster.Type == "Boss")
		{
			Log.AddLog("Dragon은 Boss 노드에서만 등장합니다.");
			continue;
		}

		ValidEncounters.push_back(Encounter);
	}

	if (ValidEncounters.empty())
	{
		Log.AddLog("사용 가능한 전투 후보가 없습니다.");
		return false;
	}

	static std::mt19937 Generator{ std::random_device{}() };
	std::uniform_int_distribution<int> Distribution(0, static_cast<int>(ValidEncounters.size()) - 1);

	OutEncounter = ValidEncounters[Distribution(Generator)];
	return true;
}

bool TryBuildBossBattleStartData(const MapNode& CurrentNode, BattleStartData& OutBattleStartData, LogManager& Log)
{
	BattleMonsterStartData Dragon;

	if (!TryFindMonsterStartData(7, Dragon))
	{
		Log.AddLog("Dragon 데이터를 찾을 수 없습니다.");
		return false;
	}

	OutBattleStartData = {};
	OutBattleStartData.bIsBoss = true;
	OutBattleStartData.Floor = CurrentNode.Floor;
	OutBattleStartData.Monsters.push_back(Dragon);
	return true;
}

bool TryBuildBattleStartData(const MapNode& CurrentNode, BattleStartData& OutBattleStartData, LogManager& Log)
{
	if (CurrentNode.Type == ENodeType::Boss)
	{
		return TryBuildBossBattleStartData(CurrentNode, OutBattleStartData, Log);
	}

	MapEncounter SelectedEncounter;

	if (!TrySelectEncounterForFloor(CurrentNode.Floor, SelectedEncounter, Log))
	{
		return false;
	}

	BattleMonsterStartData Monster;

	if (!TryFindMonsterStartData(SelectedEncounter.MonsterId, Monster))
	{
		Log.AddLog("몬스터 데이터를 찾을 수 없습니다. Id: " + std::to_string(SelectedEncounter.MonsterId));
		return false;
	}

	OutBattleStartData = {};
	OutBattleStartData.bIsBoss = false;
	OutBattleStartData.Floor = CurrentNode.Floor;

	for (int i = 0; i < SelectedEncounter.Count; i++)
	{
		OutBattleStartData.Monsters.push_back(Monster);
	}

	return !OutBattleStartData.Monsters.empty();
}
}

State_Map::State_Map()
{
	Name = "Map";
}

void State_Map::Enter()
{
	ConsoleUtil::HideCursor();
	GSharedSaveMgr->SaveSnapShot();
}

void State_Map::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();
	MapManager& Map = Instance.GetMapManager();
	LogManager& Log = Instance.GetLogManager();

	Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
	assert(LoadPlayer && "LoadPlayer is null");
	
	GameScreen::DrawMainScreen(
		Map,
		Log,
		LoadPlayer
	);

	if (!GameProgress::HandleNodeSelection(Map, Log))
	{
		return;
	}

	const MapNode* CurrentNode = Map.GetCurrentNode();

	if (CurrentNode == nullptr)
	{
		Log.AddLog("현재 노드 정보를 찾을 수 없습니다.");
		return;
	}

	GameProgress::HandleCurrentNodeEvent(Map, Log);

	if (CurrentNode->Type == ENodeType::Event)
	{
		HandleEventNode(LoadPlayer, Log);
		GameScreen::DrawCharacterPanel(LoadPlayer);
		GameScreen::DrawLogPanel(Log);
		return;
	}

	if (IsBattleNode(CurrentNode->Type))
	{
		BattleStartData BattleData;

		if (!TryBuildBattleStartData(*CurrentNode, BattleData, Log))
		{
			return;
		}

		Instance.SetBattleStartData(BattleData);
		StateManager::GetInstance().ChangeState(EState::Combat);
		return;
	}

	if (CurrentNode->Type == ENodeType::Shop)
	{
		StateManager::GetInstance().ChangeState(EState::Shop);
	}
}

void State_Map::Exit()
{
}

void State_Map::HandleEventNode(Player* MainPlayer, LogManager& Log)
{
	if (MainPlayer == nullptr)
	{
		Log.AddLog("? 이벤트를 처리할 플레이어를 찾을 수 없습니다.");
		return;
	}

	static std::mt19937 Generator{ std::random_device{}() };
	std::uniform_int_distribution<int> Distribution(0, 1);

	const int EventType = Distribution(Generator);
	constexpr int EventHpAmount = 20;

	if (EventType == 0)
	{
		MainPlayer->Recovery(EResourceType::Health, EventHpAmount);
		Log.AddLog("? 이벤트 발생! 신비한 샘을 발견했습니다. 체력을 20 회복했습니다.");
		return;
	}

	MainPlayer->TakeDamage(EventHpAmount);
	Log.AddLog("? 이벤트 발생! 숨겨진 함정이 발동했습니다. 체력을 20 잃었습니다.");
}
