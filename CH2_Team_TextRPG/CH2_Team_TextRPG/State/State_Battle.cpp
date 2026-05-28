#include "pch.h"
#include "Combat/BattleUI.h"
#include "Combat/CombatCondition.h"
#include "Character/Component/EffectComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Character/Monster/MonsterFactory.h"
#include "Data/Table/SkillDataTable.h"
#include "Data/Table/ItemDataTable.h"
#include "Manager/ObjectManager.h"
#include "Manager/CombatManager.h"
#include "State_Battle.h"

using namespace std;

State_Battle::State_Battle()
{
	Name = "Battle";

	AddTransition<CombatVictoryCondition>(EState::CombatEnd);
	AddTransition<CombatDefeatCondition>(EState::Result);
}

State_Battle::~State_Battle()
{
}

void State_Battle::Enter()
{
	Player* PlayerCharacter = GameInstance::GetInstance().GetMainPlayer();

	const BattleStartData* StartData = GameInstance::GetInstance().GetBattleStartData();

	vector<Monster*> Monsters;
	for (const BattleMonsterStartData& data : StartData->Monsters)
	{
		Monster* NewMonster = MonsterFactory::CreateForPlayer(data.Name, PlayerCharacter);
		if (NewMonster)
		{
			Monsters.emplace_back(NewMonster);
		}
	}
	CombatManager::GetInstance().Initialize(PlayerCharacter, Monsters);
}

void State_Battle::Process()
{
	if (CombatManager::GetInstance().IsBattleEnd())
	{
		return;
	}

	Object* CurTurnCharacter = CombatManager::GetInstance().GetNextTurnCharacter();
	if (!CurTurnCharacter) return;
	
	auto EffectComp = CurTurnCharacter->FindComponent<EffectComponent>("Effect");
	bool bIsStunned = false;
	if (EffectComp)
	{
		bIsStunned = EffectComp->HasEffectByTag("State_Stun");
		EffectComp->UpdateEffects();
		EffectComp->RemoveExpiredEffects();
	}

	if (Player* PlayerChar = dynamic_cast<Player*>(CurTurnCharacter))
	{
		if (PlayerChar->IsDead()) return;
		if (bIsStunned)
		{
			GLog.AddLog("[상태이상] " + PlayerChar->GetName() + "은(는) 기절하여 턴을 넘깁니다.");
			return;
		}
		HandlePlayerTurn(PlayerChar);
	}
	else if (Monster* MonsterChar = dynamic_cast<Monster*>(CurTurnCharacter))
	{
		if (MonsterChar->IsDead()) return;
		if (bIsStunned)
		{
			GLog.AddLog("[상태이상] " + MonsterChar->GetName() + "은(는) 기절하여 턴을 넘깁니다.");
			return;
		}
		HandleMonsterTurn(MonsterChar);
	}
}

void State_Battle::Exit()
{
	// TODO : 전투 종료 시 효과 제거 (버프/디버프 등)
	GameInstance::GetInstance().GetMainPlayer()->FindComponent<EffectComponent>("Effect");
	CombatManager::GetInstance().Clear();
}


void State_Battle::HandlePlayerTurn(Player* PlayerCharacter)
{
	bool bTurnEnded = false;
	while (!bTurnEnded)
	{
		EActionType Action = BattleUI::ShowActionMenu();
		auto SkillComp = PlayerCharacter->FindComponent<SkillComponent>("Skill");
		std::vector<Monster*> AliveMonsters = CombatManager::GetInstance().GetAliveMonsters();

		if (Action == EActionType::ATTACK)
		{
			if (SkillComp && !SkillComp->GetLearnedSkills().empty())
			{
				Skill* BasicAttack = SkillComp->GetLearnedSkills()[0];
				auto Targets = BattleUI::ShowTargetMenu(AliveMonsters, 1);
				
				if (!Targets.empty())
				{
					CombatManager::GetInstance().ExecuteSkill(PlayerCharacter, Targets, BasicAttack);
					bTurnEnded = true;
				}
			}
		}
		else if (Action == EActionType::SKILL)
		{
			Skill* SelectedSkill = BattleUI::ShowSkillMenu(SkillComp);
			if (SelectedSkill)
			{
				int TargetCount = (SelectedSkill->GetSkillData()->TargetType == ETargetType::ALL_ENEMIES) ? AliveMonsters.size() : 1;
				vector<Object*> Targets = BattleUI::ShowTargetMenu(AliveMonsters, TargetCount);
				
				if (!Targets.empty())
				{
					CombatManager::GetInstance().ExecuteSkill(PlayerCharacter, Targets, SelectedSkill);
					bTurnEnded = true;
				}
			}
		}
		else if (Action == EActionType::ITEM)
		{
			GInput << "아이템 기능은 아직 구현되지 않았습니다.\n";
		}
	}
}

void State_Battle::HandleMonsterTurn(Monster* MonsterCharacter)
{
	auto SkillComp = MonsterCharacter->FindComponent<SkillComponent>("Skill");
	if (SkillComp && !SkillComp->GetLearnedSkills().empty())
	{
		Skill* BasicAttack = SkillComp->GetLearnedSkills()[0];
		Player* PlayerCharacter = GameInstance::GetInstance().GetMainPlayer();
		
		if (PlayerCharacter && !PlayerCharacter->IsDead())
		{
			std::vector<Object*> Targets = { PlayerCharacter };
			CombatManager::GetInstance().ExecuteSkill(MonsterCharacter, Targets, BasicAttack);
		}
	}
}