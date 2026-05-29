#pragma once

#include "Core/State.h"

class LogManager;
class Player;

class State_Map : public BaseState
{
public:
	State_Map();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	void HandleEventNode(Player* MainPlayer, LogManager& Log);
};
