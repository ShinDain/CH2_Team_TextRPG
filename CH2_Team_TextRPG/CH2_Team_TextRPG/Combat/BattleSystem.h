#pragma once

#include "Combat/BattleStartData.h"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

class Player;
struct FSkillData;

struct BattleSkillOption
{
	uint16_t SkillId = 0;
	std::string Name;
	int ManaCost = 0;
	bool bUsable = false;
};

struct BattleMonsterViewData
{
	std::string Name;
	int CurrentHP = 0;
	int MaxHP = 0;
	bool bIsDead = false;
};

struct BattleMonsterActionResult
{
	int MonsterIndex = -1;
	std::string MonsterName;
	int Damage = 0;
	int CurrentHP = 0;
	bool bKilled = false;
};

struct BattlePlayerDamageResult
{
	int MonsterIndex = -1;
	std::string MonsterName;
	int Damage = 0;
};

struct BattleTurnResult
{
	bool bSkillUsed = false;
	bool bVictory = false;
	bool bDefeat = false;
	uint16_t SkillId = 0;
	std::string SkillName;
	std::string Message;
	std::vector<BattleMonsterActionResult> MonsterHits;
	std::vector<BattlePlayerDamageResult> PlayerHits;
};

class BattleSystem
{
public:
	bool Initialize(Player* InPlayer, const BattleStartData& InStartData);
	void Clear();

	BattleTurnResult UseSkill(uint16_t SkillId);

	bool IsBossBattle() const { return StartData.bIsBoss; }
	bool IsBattleOver() const;
	bool IsVictory() const;
	bool IsDefeat() const;

	std::vector<BattleMonsterViewData> GetMonsterViews() const;
	std::vector<BattleSkillOption> GetSkillOptions() const;

private:
	struct RuntimeMonster
	{
		BattleMonsterStartData StartData;
		int CurrentHP = 0;
	};

	Player* PlayerCharacter = nullptr;
	BattleStartData StartData;
	std::vector<RuntimeMonster> Monsters;
	std::unordered_map<uint16_t, int> Cooldowns;

	const FSkillData* FindSkillData(uint16_t SkillId) const;
	std::vector<const FSkillData*> GetKnownPlayerSkills() const;
	int FindFirstAliveMonsterIndex() const;
	std::vector<int> SelectTargets(const FSkillData* SkillData) const;
	int CalculatePlayerDamage(const FSkillData* SkillData, const RuntimeMonster& Monster) const;
	void ApplySkillCooldowns(uint16_t UsedSkillId);
	void RunMonsterTurn(BattleTurnResult& Result);
};
