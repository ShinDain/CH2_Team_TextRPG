#include "pch.h"
#include "State_Start.h"
#include "UI/BattleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "Core/GameInstance.h"
#include "Core/GameProgress.h"
#include "Data/JsonDataParser.h"
#include "Data/Table/MonsterDataTable.h"
#include "UI/GameScreen.h"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <random>
#include <windows.h>

namespace
{
struct MapEncounter
{
	uint32_t MonsterId = 0;
	int Count = 0;
};

struct MonsterLookupResult
{
	std::string Name;
	std::string Type;
	int HP = 0;
};

bool IsBattleNode(ENodeType Type)
{
	return Type == ENodeType::Monster ||
		Type == ENodeType::Elite ||
		Type == ENodeType::Boss;
}

bool IsRegularBattleMonsterId(uint32_t MonsterId)
{
	return MonsterId >= 1 && MonsterId <= 6;
}

std::string ToLowerCopy(const std::string& Text)
{
	std::string LowerText = Text;

	std::transform(
		LowerText.begin(),
		LowerText.end(),
		LowerText.begin(),
		[](unsigned char Character)
		{
			return static_cast<char>(std::tolower(Character));
		}
	);

	return LowerText;
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

	Log.AddLog("현재 층의 전투 데이터를 찾을 수 없습니다.");
	return false;
}

bool TryFindMonsterById(uint32_t MonsterId, MonsterLookupResult& OutMonster)
{
	const MonsterData* Monster = MonsterDataTable::GetInstance().FindMonsterDataById(MonsterId);

	if (Monster != nullptr)
	{
		OutMonster.Name = Monster->Name;
		OutMonster.Type = Monster->Type;
		OutMonster.HP = static_cast<int>(Monster->HP);
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
			!MonsterDataJson.contains("HP"))
		{
			continue;
		}

		if (MonsterDataJson["Id"].get<uint32_t>() == MonsterId)
		{
			OutMonster.Name = MonsterDataJson["Name"].get<std::string>();
			OutMonster.Type = MonsterDataJson["Type"].get<std::string>();
			OutMonster.HP = MonsterDataJson["HP"].get<int>();
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
		MonsterLookupResult Monster;

		if (!IsRegularBattleMonsterId(Encounter.MonsterId))
		{
			Log.AddLog("일반 전투에서 사용하지 않는 몬스터를 제외했습니다. Id: " + std::to_string(Encounter.MonsterId));
			continue;
		}

		if (!TryFindMonsterById(Encounter.MonsterId, Monster))
		{
			Log.AddLog("몬스터 데이터를 찾을 수 없습니다. Id: " + std::to_string(Encounter.MonsterId));
			continue;
		}

		if (Monster.Type == "Boss")
		{
			Log.AddLog("일반 전투에서 Boss 몬스터를 제외했습니다. Id: " + std::to_string(Encounter.MonsterId));
			continue;
		}

		ValidEncounters.push_back(Encounter);
	}

	if (ValidEncounters.empty())
	{
		Log.AddLog("현재 층에서 사용할 수 있는 전투 후보가 없습니다.");
		return false;
	}

	static std::mt19937 Generator{ std::random_device{}() };
	std::uniform_int_distribution<int> Distribution(0, static_cast<int>(ValidEncounters.size()) - 1);

	OutEncounter = ValidEncounters[Distribution(Generator)];
	return true;
}

std::vector<std::pair<int, int>> MakeMonsterPositions(int MonsterCount)
{
	if (MonsterCount <= 1)
	{
		return { { 105, 8 } };
	}

	return { { 80, 8 }, { 130, 8 } };
}

bool PlayBossBattle()
{
	MonsterLookupResult Monster;
	const int MonsterHP = TryFindMonsterById(7, Monster) ? Monster.HP : 250;
	const std::string MonsterName = Monster.Name.empty() ? "dragon" : ToLowerCopy(Monster.Name);

	BattleRenderer BattleRenderer;
	BattleRenderer.ClearMonsters();
	BattleRenderer.SetMonsterName(MonsterName);
	BattleRenderer.AddMonster(MonsterName, 105, 6, MonsterHP, MonsterHP);
	BattleRenderer.PlayNormalBattleAnimation();
	return true;
}

bool PlayCurrentNodeBattle(GameInstance& Instance)
{
	const MapNode* CurrentNode = Instance.GetMapManager().GetCurrentNode();

	if (CurrentNode == nullptr || !IsBattleNode(CurrentNode->Type))
	{
		return false;
	}

	if (CurrentNode->Type == ENodeType::Boss)
	{
		return PlayBossBattle();
	}

	LogManager& Log = Instance.GetLogManager();
	MapEncounter SelectedEncounter;

	if (!TrySelectEncounterForFloor(CurrentNode->Floor, SelectedEncounter, Log))
	{
		return false;
	}

	MonsterLookupResult Monster;

	if (!TryFindMonsterById(SelectedEncounter.MonsterId, Monster))
	{
		Log.AddLog("몬스터 데이터를 찾을 수 없습니다. Id: " + std::to_string(SelectedEncounter.MonsterId));
		return false;
	}

	const std::string MonsterName = ToLowerCopy(Monster.Name);
	const int MonsterCount = SelectedEncounter.Count < 2 ? SelectedEncounter.Count : 2;
	const std::vector<std::pair<int, int>> Positions = MakeMonsterPositions(MonsterCount);

	BattleRenderer BattleRenderer;
	BattleRenderer.ClearMonsters();
	BattleRenderer.SetMonsterName(MonsterName);

	for (int i = 0; i < MonsterCount; i++)
	{
		BattleRenderer.AddMonster(MonsterName, Positions[i].first, Positions[i].second, Monster.HP, Monster.HP);
	}

	BattleRenderer.PlayNormalBattleAnimation();
	return true;
}

void ProcessCurrentNodeBattleAndBossEnd(GameInstance& Instance)
{
	const MapNode* CurrentNode = Instance.GetMapManager().GetCurrentNode();

	if (CurrentNode == nullptr)
	{
		return;
	}

	const bool bBattlePlayed = PlayCurrentNodeBattle(Instance);

	if (CurrentNode->Type == ENodeType::Boss)
	{
		GameProgress::EndGame(Instance.GetLogManager());
		Instance.Quit();
		return;
	}

	if (bBattlePlayed)
	{
		GameScreen::DrawMainScreen(
			Instance.GetMapManager(),
			Instance.GetLogManager(),
			Instance.GetMainPlayer()
		);
	}
}
}

State_Start::State_Start()
{
}

void State_Start::Enter()
{
	GameInstance::GetInstance().GetLogManager().AddLog("맵 화면에 진입했습니다.");
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	ConsoleUtil::HideCursor();

	GameScreen::DrawMainScreen(
		Instance.GetMapManager(),
		Instance.GetLogManager(),
		Instance.GetMainPlayer()
	);

	if (Instance.GetMapManager().IsBossNode())
	{
		GameProgress::HandleCurrentNodeEvent(
			Instance.GetMapManager(),
			Instance.GetLogManager()
		);

		ProcessCurrentNodeBattleAndBossEnd(Instance);
		return;
	}

	GameProgress::HandleNodeSelection(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);

	GameProgress::HandleCurrentNodeEvent(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);

	ProcessCurrentNodeBattleAndBossEnd(Instance);
}

void State_Start::Exit()
{
}
