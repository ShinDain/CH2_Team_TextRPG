#include "pch.h"
#include "State_Battle.h"
#include "Character/Component/SkillComponent.h"
#include "Manager/ObjectManager.h"
#include "Manager/CombatManager.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Data/Table/SkillDataTable.h"
#include "Data/Table/ItemDataTable.h"
#include "CombatCondition.h"
#include "BattleUI.h"
#include <set>

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
	Player* PlayerCharacter = ObjectManager::GetInstance().FindObject<Player>("Player");
	
	// TODO : 몬스터 데이터 추가필요
	std::vector<Monster*> Monsters;
	
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
	
	// TODO : 상태이상 컴포넌트 처리
	// 턴 시작 시 캐릭터의 상태이상 효과(독, 화상 등)를 적용합니다.
	// CurTurnCharacter->FindComponent<EffectComponent>("Effect")->UpdateEffects();

	// 상태이상 데미지로 캐릭터가 사망했는지 확인합니다.
	//if (CurTurnCharacter->IsDead())
	//{
		//return;
	//}

	if (Player* PlayerChar = dynamic_cast<Player*>(CurTurnCharacter))
	{
		HandlePlayerTurn(PlayerChar);
	}
	else if (Monster* MonsterChar = dynamic_cast<Monster*>(CurTurnCharacter))
	{
		HandleMonsterTurn(MonsterChar);
	}
}

void State_Battle::Exit()
{
	// TODO: 전투 중에만 적용되는 버프/디버프를 플레이어의 EffectComponent에서 제거합니다.
	
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
				auto Targets = BattleUI::ShowTargetMenu(AliveMonsters, TargetCount);
				
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
		Player* PlayerCharacter = ObjectManager::GetInstance().FindObject<Player>("Player");
		
		if (PlayerCharacter && !PlayerCharacter->IsDead())
		{
			std::vector<Object*> Targets = { PlayerCharacter };
			CombatManager::GetInstance().ExecuteSkill(MonsterCharacter, Targets, BasicAttack);
		}
	}
}