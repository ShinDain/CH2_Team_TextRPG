#pragma once

#include "Core/State.h"

class State_Ending : public BaseState
{
public:
	State_Ending();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};
