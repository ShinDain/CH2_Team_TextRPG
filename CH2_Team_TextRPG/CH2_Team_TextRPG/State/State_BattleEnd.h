#pragma once
#include "Core/State.h"

class State_BattleEnd : public BaseState
{
public:
	State_BattleEnd();
	virtual ~State_BattleEnd() override;

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};