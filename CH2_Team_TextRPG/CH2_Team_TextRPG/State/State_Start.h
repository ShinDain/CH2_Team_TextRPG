#pragma once

#include "Core/State.h"

class State_Start : public BaseState
{
public:
	State_Start();
protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};

