#pragma once

#include "Core/State.h"

class State_Result : public BaseState
{
public:
	State_Result();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};
