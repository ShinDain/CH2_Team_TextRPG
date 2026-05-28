#pragma once

#include "Core/State.h"

class State_Map : public BaseState
{
public:
	State_Map();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;
};
