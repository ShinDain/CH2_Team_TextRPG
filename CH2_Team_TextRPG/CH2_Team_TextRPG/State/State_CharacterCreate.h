#pragma once

#include "Core/State.h"
#include "Data/Character/CharacterJobData.h"
#include <vector>

class State_CharacterCreate : public BaseState
{
public:
	State_CharacterCreate();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	std::vector<CharacterJobData> Jobs;
};
