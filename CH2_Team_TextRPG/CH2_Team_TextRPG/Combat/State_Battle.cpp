#include "pch.h"
#include "State_Battle.h"
#include "Character/Component/SkillComponent.h"
#include "Manager/ObjectManager.h"
#include "Manager/TurnManager.h"
#include "Manager/CombatManager.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Data/Table/SkillDataTable.h"
#include "Data/Table/ItemDataTable.h"
#include "CombatCondition.h"
#include <set>

using namespace std;

State_Battle::State_Battle()
{
	Name = "Battle";
	CurActionType = EActionType::ATTACK;
	CurBattleState = EBattleState::NEXT_TURN;
	CurTurnCharacter = nullptr;
	PlayerCharacter = nullptr;
	SelectedSkillData = nullptr;
	TargetList.clear();
	if (TurnManagerInst == nullptr)
	{
		TurnManagerInst = new TurnManager();
	}
	AddTransition<CombatVictoryCondition>(EState::CombatEnd);
	AddTransition<CombatDefeatCondition>(EState::Result);
}

void State_Battle::Enter()
{
	PlayerCharacter = ObjectManager::GetInstance().FindObject<Player>("Player");
	TurnManagerInst->AddCharacterToTimeline(PlayerCharacter);
	DisplayNames[PlayerCharacter] = PlayerCharacter->GetName();

	// TODO : 몬스터 데이터 추가필요

	char MonsterSuffix = 'A';
	for(Monster* monster : Monsters)
	{
		 TurnManagerInst->AddCharacterToTimeline(monster);
		 DisplayNames[monster] = monster->GetName() + MonsterSuffix;
		 MonsterSuffix++;
	}
}

void State_Battle::Process()
{
	switch (CurBattleState)
	{
	case EBattleState::NEXT_TURN:
		ProcessNextTurn();
		break;
	case EBattleState::INPUT_ACTION:
		ProcessInputAction();
		break;
	case EBattleState::INPUT_SKILL:
		ProcessInputSkill();
		break;
	case EBattleState::INPUT_ITEM:
		ProcessInputItem();
		break;
	case EBattleState::INPUT_TARGET:
		ProcessInputTarget();
		break;
	case EBattleState::MONSTER_ACTION:
		ProcessMonsterAction();
		break;
	case EBattleState::ACTION:
		ProcessAction();
		break;
	case EBattleState::END:
		ProcessEnd();
		break;
	}
}

void State_Battle::ProcessNextTurn()
{
	CurTurnCharacter = TurnManagerInst->GetNextTurnCharacter();
	// TODO : 게이지 상승 연출
	// TODO : CurTurnCharacter가 플레이어인지 몬스터인지 판별하는 로직 필요
	// if (CurTurnCharacter->IsPlayer())
	// 	CurBattleState = EBattleState::INPUT_ACTION;
	// else
	// 	CurBattleState = EBattleState::MONSTER_ACTION;
	
	CurBattleState = EBattleState::INPUT_ACTION; // 임시 전환
}

void State_Battle::ProcessInputAction()
{
	CurTurnCharacter = PlayerCharacter;

	int InputChoice = -1;
	bool bValidInput = false;

	while (!bValidInput)
	{
		GInput << "어떤 행동을 하시겠습니까?" << "\n" << "1. 공격" << "\n" << "2. 스킬" << "\n" << "3. 아이템" << "\n";
		GInput >> InputChoice;

		if (GInput.IsFailed())
		{
			GInput << "유효하지 않은 입력입니다. 1, 2, 3 중 하나를 입력해주세요.\n";
		}
		else
		{
			if (InputChoice >= 1 && InputChoice <= 3)
			{
				CurActionType = static_cast<EActionType>(InputChoice - 1);
				bValidInput = true;
			}
			else
			{
				GInput << "유효하지 않은 선택입니다. 1, 2, 3 중 하나를 입력해주세요.\n";
			}
		}
	}

	switch (CurActionType)
	{
		case EActionType::ATTACK:
		{
			CurBattleState = EBattleState::INPUT_TARGET;
			break;
		}
		case EActionType::SKILL:
		{
			CurBattleState = EBattleState::INPUT_SKILL;
			break;
		}
		case EActionType::ITEM:
		{
			CurBattleState = EBattleState::INPUT_ITEM;
			break;
		}
	}
}

void State_Battle::ProcessInputSkill()
{
	SkillComponent* playerSkillComponent = PlayerCharacter->FindComponent<SkillComponent>("Skill");
	if (!playerSkillComponent)
	{
		GInput << "Error: Player does not have a SkillComponent!\n";
		CurBattleState = EBattleState::INPUT_ACTION; // 행동 선택으로 돌아가기
		return;
	}

	std::set<uint16_t> LearnedSkills = playerSkillComponent->GetLearnedSkills();

	GInput << "스킬을 선택하세요.\n";
	int skillOptionIndex = 1;
	for (uint16_t skillId : LearnedSkills)
	{
	    const FSkillData* skillData = SkillDataTable::GetInstance().FindSkillDataByIndex(skillId);
	    if (skillData)
	    {
	        GInput << skillOptionIndex++ << ". " << skillData->Name << " (MP: " << skillData->ManaCost << ")\n";
	    }
	}

	int selectedOption = 0;
	GInput >> selectedOption;

	// TODO : 추후 유효성 검사 추가
	if (GInput.IsFailed() || selectedOption < 1 || selectedOption >= skillOptionIndex)
	{
		GInput << "유효하지 않은 입력입니다. 행동 선택으로 돌아갑니다.\n";
		CurBattleState = EBattleState::INPUT_ACTION;
		return;
	}
	//SelectedSkillData = SkillDataTable::GetInstance().FindSkillDataByIndex(*std::next(LearnedSkills.begin(), selectedOption - 1));
	CurBattleState = EBattleState::INPUT_TARGET;
}

void State_Battle::ProcessInputItem()
{
	// TODO : 인벤토리내 아이템 목록 가져오기
	// GInput << "Select Your Item";
	CurBattleState = EBattleState::INPUT_TARGET;
}

void State_Battle::ProcessInputTarget()
{
	TargetList.clear();
	bool bNeedsEnemySelection = false;

	if (CurActionType == EActionType::ATTACK)
	{
		bNeedsEnemySelection = true;
	}
	else if (CurActionType == EActionType::SKILL || CurActionType == EActionType::ITEM)
	{
		if (SelectedSkillData)
		{
			//if (SelectedSkillData->TargetType == ETargetType::SINGLE_ENEMY)
			//{
			//	bNeedsEnemySelection = true;
			//}
			//else if (SelectedSkillData->TargetType == ETargetType::SELF || SelectedSkillData->TargetType == ETargetType::SINGLE_ALLY || SelectedSkillData->TargetType == ETargetType::ALL_ALLIES)
			//{
			//	TargetList.push_back(CurTurnCharacter);
			//}
		}
	}

	if (bNeedsEnemySelection)
	{
		std::vector<Monster*> AliveMonsters;
		GInput << "대상을 선택하세요.\n";
		for (size_t i = 0; i < Monsters.size(); ++i)
		{
			// TODO: 몬스터 사망 체크 
			// if(!Monsters[i]->IsDead())
			AliveMonsters.push_back(Monsters[i]);
			GInput << AliveMonsters.size() << ". " << DisplayNames[Monsters[i]] << "\n";
		}

		int SelectIdx = 0;
		GInput >> SelectIdx;
		if (SelectIdx > 0 && SelectIdx <= AliveMonsters.size())
		{
			TargetList.push_back(AliveMonsters[SelectIdx - 1]);
		}

		// TODO : 임시 첫번째 유닛 선택
		if (!AliveMonsters.empty() && TargetList.empty())
		{
			TargetList.push_back(AliveMonsters[0]);
		}
	}

	CurBattleState = EBattleState::ACTION;
}

void State_Battle::ProcessMonsterAction()
{
	// TODO : 몬스터 패턴에 따른 스킬/공격 결정
	CurActionType = EActionType::ATTACK;
	TargetList.push_back(PlayerCharacter);
	CurBattleState = EBattleState::ACTION;
}

void State_Battle::ProcessAction()
{
	std::vector<Effect*> EffectsToApply;

	switch (CurActionType)
	{
	case EActionType::ATTACK:
        // TODO : 추후 평타전용 Effect로 변경
		CombatManager::ExecuteBasicAttack(CurTurnCharacter, TargetList[0]);
		break;
        
	case EActionType::SKILL:
		// TODO : 코스트 지불
        // PlayerCharacter->FindComponent<SkillComponent>("Skill")->ConsumeCost(SelectedSkillData->Idx);
        
		//EffectsToApply = SelectedSkillData->Effects;
		break;
        
	case EActionType::ITEM:
		// TODO : 코스트 지불
        // PlayerCharacter->FindComponent<InventoryComponent>("Inventory")->UseItem(SelectedItemData->Id);
        
		//EffectsToApply = SelectedItemData->Effects;
		break;
	}

    if (!EffectsToApply.empty())
    {
	    //CombatManager::ApplyEffects(CurTurnCharacter, TargetList, EffectsToApply);
    }

	// 행동 수치(Action Value) 초기화
	if (CurTurnCharacter)
	{
		TurnManagerInst->ResetCharacterTurn(CurTurnCharacter);
	}

	// TODO : 다음 턴을 위해 다시 NEXT_TURN 상태로 돌아가거나, 승패 조건 달성 시 END로 전환
	CurBattleState = EBattleState::NEXT_TURN;
}

void State_Battle::ProcessEnd()
{
	// TODO : 전투 승패 처리 및 보상 지급, 이전 상태(필드 등)로 전환
}
