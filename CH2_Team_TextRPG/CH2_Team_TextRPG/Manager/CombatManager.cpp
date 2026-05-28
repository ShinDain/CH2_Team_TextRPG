#include "pch.h"
#include "CombatManager.h"
#include "Character/Component/StatComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"
#include "Effect/Effect.h"
#include "Character/Component/ResourceComponent.h"
#include "Character/Component/EffectComponent.h"

CombatManager& CombatManager::GetInstance()
{
	static CombatManager Instance;
	return Instance;
}

CombatManager::CombatManager()
{
	TurnManagerInst = new TurnManager();
}

CombatManager::~CombatManager()
{
	delete TurnManagerInst;
}

void CombatManager::Initialize(Player* InPlayer, const std::vector<Monster*>& InMonsters)
{
	PlayerCharacter = InPlayer;
	Monsters = InMonsters;

	if (PlayerCharacter)
		TurnManagerInst->AddCharacterToTimeline(PlayerCharacter);

	for (Monster* monster : Monsters)
		TurnManagerInst->AddCharacterToTimeline(monster);
}

void CombatManager::Clear()
{
	PlayerCharacter = nullptr;
	
	for (Monster* monster : Monsters)
	{
		ObjectManager::GetInstance().RemoveObject(monster);
	}
	Monsters.clear();

	delete TurnManagerInst;
	TurnManagerInst = new TurnManager();
}

Object* CombatManager::GetNextTurnCharacter()
{
	Object* nextChar = TurnManagerInst->GetNextTurnCharacter();
	if (nextChar) TurnManagerInst->ResetCharacterTurn(nextChar);
	return nextChar;
}

std::vector<Monster*> CombatManager::GetAliveMonsters() const
{
	std::vector<Monster*> aliveMonsters;
	for (Monster* monster : Monsters)
		if (monster && !monster->IsDead()) aliveMonsters.push_back(monster);
	return aliveMonsters;
}

bool CombatManager::IsBattleEnd() const
{
	if (PlayerCharacter && PlayerCharacter->IsDead()) return true;
	if (GetAliveMonsters().empty()) return true;
	return false;
}

void CombatManager::ExecuteSkill(Object* Caster, const std::vector<Object*>& Targets, Skill* InSkill)
{
	if (!Caster || Targets.empty() || !InSkill) return;

	auto skillComp = Caster->FindComponent<SkillComponent>("Skill");
	if (skillComp)
	{
		skillComp->ConsumeCost(InSkill);
		skillComp->ApplyCooldown(InSkill);
	}
	GLog.AddLog("[시스템] " + Caster->GetName() + "이(가) " + InSkill->GetSkillData()->Name + "을(를) 사용했습니다!");
	InSkill->Active(Caster, Targets);
}
