#include "pch.h"
#include "BattleSystem.h"
#include "Character/Player/Player.h"
#include "Data/Character/Damage.h"
#include "Data/Character/Stat.h"
#include "Data/JsonDataParser.h"
#include "Data/Table/SkillDataTable.h"

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

bool LoadSkillDataFallback(uint16_t SkillId, FSkillData& OutSkillData)
{
	json SkillJson;
	const std::vector<std::filesystem::path> Candidates =
		MakeScriptPathCandidates(std::filesystem::path("Script") / "Skill" / "Skill.json");

	for (const std::filesystem::path& Candidate : Candidates)
	{
		if (!std::filesystem::exists(Candidate))
		{
			continue;
		}

		if (!JsonDataParser::Load(Candidate.string(), SkillJson) || !SkillJson.is_array())
		{
			continue;
		}

		for (const json& SkillDataJson : SkillJson)
		{
			if (!SkillDataJson.contains("Idx"))
			{
				continue;
			}

			if (SkillDataJson["Idx"].get<uint16_t>() == SkillId)
			{
				OutSkillData = SkillDataJson.get<FSkillData>();
				return true;
			}
		}
	}

	return false;
}
}

bool BattleSystem::Initialize(Player* InPlayer, const BattleStartData& InStartData)
{
	Clear();

	PlayerCharacter = InPlayer;
	StartData = InStartData;

	if (PlayerCharacter == nullptr || StartData.Monsters.empty())
	{
		return false;
	}

	for (const BattleMonsterStartData& MonsterData : StartData.Monsters)
	{
		RuntimeMonster Monster;
		Monster.StartData = MonsterData;
		Monster.CurrentHP = MonsterData.HP;
		Monsters.push_back(Monster);
	}

	for (const FSkillData* SkillData : GetKnownPlayerSkills())
	{
		if (SkillData != nullptr)
		{
			Cooldowns.emplace(SkillData->Idx, 0);
		}
	}

	return true;
}

void BattleSystem::Clear()
{
	PlayerCharacter = nullptr;
	StartData = {};
	Monsters.clear();
	Cooldowns.clear();
}

BattleTurnResult BattleSystem::UseSkill(uint16_t SkillId)
{
	BattleTurnResult Result;

	if (PlayerCharacter == nullptr)
	{
		Result.Message = "플레이어 정보가 없습니다.";
		return Result;
	}

	if (IsBattleOver())
	{
		Result.bVictory = IsVictory();
		Result.bDefeat = IsDefeat();
		return Result;
	}

	const FSkillData* SkillData = FindSkillData(SkillId);

	if (SkillData == nullptr)
	{
		Result.Message = "존재하지 않는 스킬입니다.";
		return Result;
	}

	if (Cooldowns.find(SkillId) != Cooldowns.end() && Cooldowns[SkillId] > 0)
	{
		Result.Message = "아직 재사용 대기 중인 스킬입니다.";
		return Result;
	}

	if (PlayerCharacter->GetCurrentResource(EResourceType::Mana) < SkillData->ManaCost)
	{
		Result.Message = "마나가 부족합니다.";
		return Result;
	}

	if (SkillData->ManaCost > 0)
	{
		PlayerCharacter->ApplyStat(EStatType::Mana, -static_cast<int>(SkillData->ManaCost));
	}
	Result.bSkillUsed = true;
	Result.SkillId = SkillData->Idx;
	Result.SkillName = SkillData->Name;

	const std::vector<int> TargetIndexes = SelectTargets(SkillData);

	for (int TargetIndex : TargetIndexes)
	{
		if (TargetIndex < 0 || TargetIndex >= static_cast<int>(Monsters.size()))
		{
			continue;
		}

		RuntimeMonster& Monster = Monsters[TargetIndex];
		const int Damage = CalculatePlayerDamage(SkillData, Monster);
		Monster.CurrentHP -= Damage;

		if (Monster.CurrentHP < 0)
		{
			Monster.CurrentHP = 0;
		}

		Result.MonsterHits.push_back(
			{
				TargetIndex,
				Monster.StartData.Name,
				Damage,
				Monster.CurrentHP,
				Monster.CurrentHP <= 0
			}
		);
	}

	ApplySkillCooldowns(SkillId);

	if (IsVictory())
	{
		Result.bVictory = true;
		return Result;
	}

	RunMonsterTurn(Result);
	Result.bDefeat = IsDefeat();

	if (Result.bDefeat)
	{
		Result.Message = "플레이어가 쓰러졌습니다.";
	}

	return Result;
}

bool BattleSystem::IsBattleOver() const
{
	return IsVictory() || IsDefeat();
}

bool BattleSystem::IsVictory() const
{
	if (Monsters.empty())
	{
		return false;
	}

	for (const RuntimeMonster& Monster : Monsters)
	{
		if (Monster.CurrentHP > 0)
		{
			return false;
		}
	}

	return true;
}

bool BattleSystem::IsDefeat() const
{
	return PlayerCharacter != nullptr && PlayerCharacter->IsDead();
}

std::vector<BattleMonsterViewData> BattleSystem::GetMonsterViews() const
{
	std::vector<BattleMonsterViewData> Views;

	for (const RuntimeMonster& Monster : Monsters)
	{
		Views.push_back(
			{
				Monster.StartData.Name,
				Monster.CurrentHP,
				Monster.StartData.HP,
				Monster.CurrentHP <= 0
			}
		);
	}

	return Views;
}

std::vector<BattleSkillOption> BattleSystem::GetSkillOptions() const
{
	std::vector<BattleSkillOption> Options;

	for (const FSkillData* SkillData : GetKnownPlayerSkills())
	{
		if (SkillData == nullptr)
		{
			continue;
		}

		const auto CooldownIter = Cooldowns.find(SkillData->Idx);
		const bool bCooldownReady = CooldownIter == Cooldowns.end() || CooldownIter->second <= 0;
		const bool bCanPay = PlayerCharacter != nullptr &&
			PlayerCharacter->GetCurrentResource(EResourceType::Mana) >= SkillData->ManaCost;

		Options.push_back(
			{
				SkillData->Idx,
				SkillData->Name,
				static_cast<int>(SkillData->ManaCost),
				bCooldownReady && bCanPay
			}
		);
	}

	return Options;
}

const FSkillData* BattleSystem::FindSkillData(uint16_t SkillId) const
{
	const FSkillData* TableData = SkillDataTable::GetInstance().FindSkillDataByIndex(SkillId);

	if (TableData != nullptr)
	{
		return TableData;
	}

	static std::unordered_map<uint16_t, FSkillData> FallbackSkills;
	auto FoundSkill = FallbackSkills.find(SkillId);

	if (FoundSkill != FallbackSkills.end())
	{
		return &FoundSkill->second;
	}

	FSkillData LoadedSkill;

	if (LoadSkillDataFallback(SkillId, LoadedSkill))
	{
		FallbackSkills.emplace(SkillId, LoadedSkill);
		return &FallbackSkills[SkillId];
	}

	return nullptr;
}

std::vector<const FSkillData*> BattleSystem::GetKnownPlayerSkills() const
{
	std::vector<const FSkillData*> Skills;
	const std::vector<uint16_t> SkillIds = { 1, 101, 102, 103 };

	for (uint16_t SkillId : SkillIds)
	{
		const FSkillData* SkillData = FindSkillData(SkillId);

		if (SkillData != nullptr)
		{
			Skills.push_back(SkillData);
		}
	}

	return Skills;
}

int BattleSystem::FindFirstAliveMonsterIndex() const
{
	for (int i = 0; i < static_cast<int>(Monsters.size()); i++)
	{
		if (Monsters[i].CurrentHP > 0)
		{
			return i;
		}
	}

	return -1;
}

std::vector<int> BattleSystem::SelectTargets(const FSkillData* SkillData) const
{
	std::vector<int> Targets;

	if (SkillData == nullptr)
	{
		return Targets;
	}

	if (SkillData->TargetType == ETargetType::ALL_ENEMIES)
	{
		for (int i = 0; i < static_cast<int>(Monsters.size()); i++)
		{
			if (Monsters[i].CurrentHP > 0)
			{
				Targets.push_back(i);
			}
		}

		return Targets;
	}

	const int TargetIndex = FindFirstAliveMonsterIndex();

	if (TargetIndex >= 0)
	{
		Targets.push_back(TargetIndex);
	}

	return Targets;
}

int BattleSystem::CalculatePlayerDamage(const FSkillData* SkillData, const RuntimeMonster& Monster) const
{
	if (PlayerCharacter == nullptr || SkillData == nullptr)
	{
		return 0;
	}

	int EffectValue = 100;

	for (const EffectData& Effect : SkillData->Effects)
	{
		if (Effect.Tag.find("Damage") != std::string::npos)
		{
			EffectValue = Effect.Value;
			break;
		}
	}

	const int Attack = PlayerCharacter->GetStat(EStatType::Attack);
	const int HitCount = SkillData->HitCount <= 0 ? 1 : SkillData->HitCount;
	const int Defense = Monster.StartData.Defense < 0 ? 0 : Monster.StartData.Defense;
	int DamagePerHit = (Attack * EffectValue) / 100 - Defense;

	if (DamagePerHit < 1)
	{
		DamagePerHit = 1;
	}

	return DamagePerHit * HitCount;
}

void BattleSystem::ApplySkillCooldowns(uint16_t UsedSkillId)
{
	for (auto& Cooldown : Cooldowns)
	{
		if (Cooldown.second > 0)
		{
			Cooldown.second--;
		}
	}

	const FSkillData* SkillData = FindSkillData(UsedSkillId);

	if (SkillData != nullptr)
	{
		Cooldowns[UsedSkillId] = SkillData->Cooldown;
	}
}

void BattleSystem::RunMonsterTurn(BattleTurnResult& Result)
{
	if (PlayerCharacter == nullptr)
	{
		return;
	}

	for (int i = 0; i < static_cast<int>(Monsters.size()); i++)
	{
		const RuntimeMonster& Monster = Monsters[i];

		if (Monster.CurrentHP <= 0)
		{
			continue;
		}

		const int BeforeHP = PlayerCharacter->GetCurrentResource(EResourceType::Health);
		DamageContext Context;
		Context.Attack = Monster.StartData.Attack;
		Context.AttackCount = 1;
		Context.SkillMultiplier = 1.0f;
		PlayerCharacter->TakeDamage(Context);
		const int AfterHP = PlayerCharacter->GetCurrentResource(EResourceType::Health);

		Result.PlayerHits.push_back({ i, Monster.StartData.Name, BeforeHP - AfterHP });

		if (PlayerCharacter->IsDead())
		{
			break;
		}
	}
}
