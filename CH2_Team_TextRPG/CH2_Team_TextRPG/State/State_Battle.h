#pragma once

#include "Core/State.h"

class Player;
class Monster;

class State_Battle : public BaseState
{
public:
	State_Battle();
	~State_Battle() override;

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:

	// 플레이어/몬스터 행동 처리
	void HandlePlayerTurn(Player* PlayerCharacter);
	void HandleMonsterTurn(Monster* MonsterCharacter);

	void BattleEnd();
};
