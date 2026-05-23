#include "pch.h"
#include "State_Battle.h"
#include "Manager/ObjectManager.h"
#include "Manager/TurnManager.h"

using namespace std;

State_Battle::State_Battle()
{
	Name = "Battle";
	CurActionType = EActionType::ATTACK;
	CurBattleState = EBattleState::NEXT_TURN;
	CurTurnCharacter = nullptr;
	PlayerCharacter = nullptr;
	Target = nullptr;
	if (TurnManagerInst == nullptr)
	{
		TurnManagerInst = new TurnManager();
	}

	//AddTransition<>();
}

void State_Battle::Enter()
{
	PlayerCharacter = ObjectManager::GetInstance().FindObject<Player>("Player");
	TurnManagerInst->AddCharacterToTimeline(PlayerCharacter);
	DisplayNames[PlayerCharacter] = PlayerCharacter->GetName();

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
	{
		CurTurnCharacter = TurnManagerInst->GetNextTurnCharacter();
		//TODO : 게이지 상승 연출

		// TODO : CurTurnCharacter가 플레이어인지 몬스터인지 판별하는 로직 필요
		// if (CurTurnCharacter->IsPlayer())
		// 	CurrentState = EBattleState::INPUT_ACTION;
		// else
		// 	CurrentState = EBattleState::MONSTER_ACTION;
		
		CurBattleState = EBattleState::INPUT_ACTION; // 임시 전환
		break;
	}
	case EBattleState::INPUT_ACTION:
	{
		//GInput << "Input Your Action" << "\n" << "1. Attack" << "\n" << "2. Skill" << "\n" << "3. Item" << "\n"; // 임시 입력 처리
		//GInput >> CurActionType;
		CurTurnCharacter = PlayerCharacter;
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
		break;
	}
	case EBattleState::INPUT_SKILL:
	{
		// TODO : 플레이어 스킬 선택 UI 출력 및 입력 처리
		CurBattleState = EBattleState::INPUT_TARGET;
		break;
	}
	case EBattleState::INPUT_ITEM:
	{
		// TODO : 플레이어 아이템 선택 UI 출력 및 입력 처리
		CurBattleState = EBattleState::INPUT_TARGET;
		break;
	}
	case EBattleState::INPUT_TARGET:
	{
		// TODO : 플레이어 행동 타겟 선택 UI 출력 및 입력 처리
		CurBattleState = EBattleState::ACTION;
		break;
	}
	case EBattleState::MONSTER_ACTION:
	{
		// TODO : 몬스터 패턴에 따른 스킬/공격 결정
		CurActionType = EActionType::ATTACK;
		Target = PlayerCharacter;
		CurBattleState = EBattleState::ACTION;
		break;
	}
	case EBattleState::ACTION:
	{
		// TODO : 결정된 행동(공격, 스킬 등) 실행 및 연출
		switch (CurActionType)
		{
		case EActionType::ATTACK:
			// TODO : 공격 실행
			break;
		case EActionType::SKILL:
			// TODO : 스킬 실행
			break;
		case EActionType::ITEM:
			// TODO : 아이템 사용
			break;
		}

		// 행동 수치(Action Value) 초기화
		if (CurTurnCharacter)
		{
			TurnManagerInst->ResetCharacterTurn(CurTurnCharacter);
		}

		// TODO : 다음 턴을 위해 다시 NEXT_TURN 상태로 돌아가거나, 승패 조건 달성 시 END로 전환
		CurBattleState = EBattleState::NEXT_TURN;
		break;
	}
	case EBattleState::END:
	{
		// TODO : 전투 승패 처리 및 보상 지급, 이전 상태(필드 등)로 전환
		break;
	}
	}
}

void State_Battle::Action_Attack(Character* player, Character* target)
{

}

void State_Battle::Action_Skill(Character* player, Character* target)
{

}

void State_Battle::Action_Item(Player* player)
{

}