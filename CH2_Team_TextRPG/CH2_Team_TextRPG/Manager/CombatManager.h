#pragma once
#include <vector>
#include "Core/Object.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Manager/TurnManager.h"
#include "Skill/Skill.h"

class CombatManager
{
private:
	CombatManager();
	~CombatManager();

public:
	static CombatManager& GetInstance();

	void Initialize(Player* InPlayer);
	void Initialize(const std::vector<Monster*>& InMonsters);
	void Initialize(Player* InPlayer, const std::vector<Monster*>& InMonsters);
	void Clear();

	Object* GetNextTurnCharacter();
	std::vector<Monster*> GetAllMonsters() const { return Monsters; };
	std::vector<Monster*> GetAliveMonsters() const;
	bool IsBattleEnd() const;
	bool IsVictory() const;

	void ExecuteSkill(Object* Caster, const std::vector<Object*>& Targets, Skill* InSkill);
	void ExecuteItem(Object* Caster, const std::vector<Object*>& Targets, int ItemId);
private:
	Player* PlayerCharacter = nullptr;
	std::vector<Monster*> Monsters;
	TurnManager* TurnManagerInst = nullptr;
};
