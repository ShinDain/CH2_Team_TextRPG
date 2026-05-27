#pragma once

#include "Core/State.h"

class State_Entry : public BaseState
{
public:
	State_Entry();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};
