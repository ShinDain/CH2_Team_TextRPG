#include "pch.h"
#include "Data/Character/CharacterJobRepository.h"
#include "Data/JsonDataParser.h"
#include "Manager/LogManager.h"

#include <filesystem>
#include <windows.h>

namespace
{
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
}

bool CharacterJobRepository::LoadCharacterJobs(std::vector<CharacterJobData>& OutJobs, LogManager& Log)
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
