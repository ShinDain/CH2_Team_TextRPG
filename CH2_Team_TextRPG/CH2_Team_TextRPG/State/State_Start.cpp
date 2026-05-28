#include "pch.h"
#include "State_Start.h"
#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Data/Character/Stat.h"
#include "Data/JsonDataParser.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

#include <filesystem>
#include <windows.h>

namespace
{
struct CharacterStatsData
{
	int Health = 0;
	int Mana = 0;
	int Attack = 0;
	int Defense = 0;
	int ActionSpeed = 0;
};

struct StartItemData
{
	int ItemId = 0;
	int Count = 0;
};

struct CharacterJobData
{
	int Id = 0;
	std::string JobName;
	std::string Description;
	CharacterStatsData Stats;
	std::vector<int> StartSkillIds;
	std::vector<StartItemData> StartItems;
};

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
	Candidates.push_back(BasePath / "CH2_Team_TextRPG" / RelativePath);

	if (BasePath.has_parent_path())
	{
		Candidates.push_back(BasePath.parent_path() / RelativePath);
		Candidates.push_back(BasePath.parent_path() / "CH2_Team_TextRPG" / RelativePath);
	}

	if (BasePath.has_parent_path() && BasePath.parent_path().has_parent_path())
	{
		Candidates.push_back(BasePath.parent_path().parent_path() / RelativePath);
		Candidates.push_back(BasePath.parent_path().parent_path() / "CH2_Team_TextRPG" / RelativePath);
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

bool TryParseCharacterJob(const json& JobJson, CharacterJobData& OutJob)
{
	if (!JobJson.contains("Id") ||
		!JobJson.contains("JobName") ||
		!JobJson.contains("Description") ||
		!JobJson.contains("Stats"))
	{
		return false;
	}

	const json& StatsJson = JobJson["Stats"];

	if (!StatsJson.contains("Health") ||
		!StatsJson.contains("Mana") ||
		!StatsJson.contains("Attack") ||
		!StatsJson.contains("Defense") ||
		!StatsJson.contains("ActionSpeed"))
	{
		return false;
	}

	OutJob.Id = JobJson["Id"].get<int>();
	OutJob.JobName = JobJson["JobName"].get<std::string>();
	OutJob.Description = JobJson["Description"].get<std::string>();
	OutJob.Stats.Health = StatsJson["Health"].get<int>();
	OutJob.Stats.Mana = StatsJson["Mana"].get<int>();
	OutJob.Stats.Attack = StatsJson["Attack"].get<int>();
	OutJob.Stats.Defense = StatsJson["Defense"].get<int>();
	OutJob.Stats.ActionSpeed = StatsJson["ActionSpeed"].get<int>();

	if (JobJson.contains("StartSkillIds") && JobJson["StartSkillIds"].is_array())
	{
		for (const json& SkillIdJson : JobJson["StartSkillIds"])
		{
			if (SkillIdJson.is_number_integer())
			{
				OutJob.StartSkillIds.push_back(SkillIdJson.get<int>());
			}
		}
	}

	if (JobJson.contains("StartItems") && JobJson["StartItems"].is_array())
	{
		for (const json& ItemJson : JobJson["StartItems"])
		{
			if (!ItemJson.is_object())
			{
				continue;
			}

			StartItemData Item;
			Item.ItemId = ItemJson.value("ItemId", 0);
			Item.Count = ItemJson.value("Count", 1);
			OutJob.StartItems.push_back(Item);
		}
	}

	return true;
}

bool LoadCharacterJobs(std::vector<CharacterJobData>& OutJobs, LogManager& Log)
{
	json CharacterJson;

	if (!LoadJsonFromCandidates(
		MakeScriptPathCandidates(std::filesystem::path("Script") / "Character" / "CharacterData.json"),
		CharacterJson) ||
		!CharacterJson.is_array())
	{
		Log.AddLog("캐릭터 데이터를 찾을 수 없습니다.");
		return false;
	}

	for (const json& JobJson : CharacterJson)
	{
		CharacterJobData Job;

		if (TryParseCharacterJob(JobJson, Job))
		{
			OutJobs.push_back(Job);
		}
	}

	if (OutJobs.empty())
	{
		Log.AddLog("선택 가능한 직업 데이터가 없습니다.");
		return false;
	}

	return true;
}

void DrawStartMenu()
{
	ConsoleUtil::HideCursor();
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(65, 12, 80, 18);
	ConsoleRenderer::SetCursorPosition(96, 15);
	GInput << "TEXT RPG";
	ConsoleRenderer::SetCursorPosition(88, 19);
	GInput << "1. 새 게임";
	ConsoleRenderer::SetCursorPosition(88, 21);
	GInput << "2. 불러오기";
	ConsoleRenderer::SetCursorPosition(88, 23);
	GInput << "0. 종료";
	ConsoleRenderer::SetCursorPosition(88, 27);
	GInput << "입력 >> ";
}

void DrawJobSelectionScreen(const std::vector<CharacterJobData>& Jobs)
{
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(45, 6, 120, 34);
	ConsoleRenderer::SetCursorPosition(92, 8);
	GInput << "직업 선택";

	for (int i = 0; i < static_cast<int>(Jobs.size()); i++)
	{
		const CharacterJobData& Job = Jobs[i];
		const int Y = 12 + (i * 7);

		ConsoleRenderer::SetCursorPosition(52, Y);
		GInput << i + 1 << ". " << Job.JobName;
		ConsoleRenderer::SetCursorPosition(52, Y + 1);
		GInput << Job.Description;
		ConsoleRenderer::SetCursorPosition(52, Y + 3);
		GInput << "HP " << Job.Stats.Health
			<< " / MP " << Job.Stats.Mana
			<< " / ATK " << Job.Stats.Attack
			<< " / DEF " << Job.Stats.Defense
			<< " / SPD " << Job.Stats.ActionSpeed;
	}

	ConsoleRenderer::SetCursorPosition(52, 37);
	GInput << "직업 번호 입력 >> ";
}

bool SelectCharacterJob(const std::vector<CharacterJobData>& Jobs, CharacterJobData& OutSelectedJob, LogManager& Log)
{
	DrawJobSelectionScreen(Jobs);

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult || Input < 1 || Input > static_cast<int>(Jobs.size()))
	{
		Log.AddLog("잘못된 직업 번호입니다.");
		return false;
	}

	OutSelectedJob = Jobs[Input - 1];
	return true;
}

void ApplyCharacterStats(Player& MainPlayer, const CharacterStatsData& Stats)
{
	MainPlayer.SetBaseStat(EStatType::Health, Stats.Health);
	MainPlayer.SetBaseStat(EStatType::Mana, Stats.Mana);
	MainPlayer.SetBaseStat(EStatType::Attack, Stats.Attack);
	MainPlayer.SetBaseStat(EStatType::Defense, Stats.Defense);
	MainPlayer.SetBaseStat(EStatType::ActionSpeed, Stats.ActionSpeed);
}

bool StartNewGameWithJobSelection(GameInstance& Instance)
{
	LogManager& Log = Instance.GetLogManager();
	std::vector<CharacterJobData> Jobs;

	if (!LoadCharacterJobs(Jobs, Log))
	{
		return false;
	}

	CharacterJobData SelectedJob;

	if (!SelectCharacterJob(Jobs, SelectedJob, Log))
	{
		return false;
	}

	Player* MainPlayer = Instance.GetMainPlayer();

	if (MainPlayer == nullptr)
	{
		Log.AddLog("플레이어 정보를 찾을 수 없습니다.");
		return false;
	}

	ApplyCharacterStats(*MainPlayer, SelectedJob.Stats);
	MainPlayer->RestoreAll();
	Instance.GetMapManager().GenerateFixedMap();
	Log.AddLog(SelectedJob.JobName + " 캐릭터를 생성했습니다.");
	StateManager::GetInstance().ChangeState(EState::Map);
	return true;
}
}

State_Start::State_Start()
{
	Name = "Start";
}

void State_Start::Enter()
{
	GameInstance::GetInstance().GetLogManager().AddLog("시작 메뉴에 진입했습니다.");
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	DrawStartMenu();

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		Instance.GetLogManager().AddLog("잘못된 입력입니다.");
		return;
	}

	switch (Input)
	{
	case 1:
		StartNewGameWithJobSelection(Instance);
		break;
	case 2:
		Instance.GetLogManager().AddLog("저장 데이터 로드는 임시로 새 게임 흐름을 사용합니다.");
		StateManager::GetInstance().ChangeState(EState::Map);
		break;
	case 0:
		Instance.Quit();
		break;
	default:
		Instance.GetLogManager().AddLog("메뉴 번호를 다시 선택해주세요.");
		break;
	}
}

void State_Start::Exit()
{
}
