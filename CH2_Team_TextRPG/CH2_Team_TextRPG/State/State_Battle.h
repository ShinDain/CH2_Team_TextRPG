#pragma once

#include "Core/State.h"
#include "Manager/TurnManager.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"

enum class EBattleState
{
	NEXT_TURN,		// 타임라인 계산 및 다음 턴 캐릭터 결정
	INPUT_ACTION,	// 플레이어 행동 선택 대기
	INPUT_SKILL,	// 플레이어 스킬 선택 대기
	INPUT_ITEM,		// 플레이어 아이템 선택 대기
	MONSTER_ACTION,	// 몬스터 행동 결정
	INPUT_TARGET,	// 플레이어 행동 타겟 선택 대기
	ACTION,			// 결정된 행동 실행 및 결과 연출
	END				// 전투 종료 체크 및 보상
};
enum class EActionType
{
	ATTACK,
	SKILL,
	ITEM
};

class State_Battle : public BaseState
{
public:
	State_Battle();

protected:
	virtual void Enter() override;
	virtual void Process() override;

private:
	EBattleState CurBattleState;
	EActionType CurActionType;
	TurnManager* TurnManagerInst;
	
	std::vector<Monster*> Monsters;
	Player* PlayerCharacter;
	Character* CurTurnCharacter;
	Character* Target;

	// UI 출력을 위한 캐릭터 포인터 ↔ 이름 매핑 테이블
	std::map<Character*, std::string> DisplayNames;

	void Action_Attack(Character* player, Character* target);
	void Action_Skill(Character* player, Character* target);
	void Action_Item(Player* player);
};
