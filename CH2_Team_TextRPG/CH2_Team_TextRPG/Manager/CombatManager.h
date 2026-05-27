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

	void Initialize(Player* InPlayer, const std::vector<Monster*>& InMonsters);
	void Clear();

	Object* GetNextTurnCharacter();
	std::vector<Monster*> GetAliveMonsters() const;
	bool IsBattleEnd() const;

	void ExecuteSkill(Object* Caster, const std::vector<Object*>& Targets, Skill* InSkill);

private:
	Player* PlayerCharacter = nullptr;
	std::vector<Monster*> Monsters;
	TurnManager* TurnManagerInst = nullptr;
};
