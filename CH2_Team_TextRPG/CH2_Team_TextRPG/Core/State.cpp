#include "pch.h"
#include "State.h"
#include "Manager/StateManager.h"

BaseState::BaseState()
{
	Transitions = {};
}

BaseState::~BaseState()
{
	for (const auto& pair : Transitions)
	{
		delete pair.second;
	}
}

EState BaseState::CanTransition() const
{
	for (const auto& pair : Transitions)
	{
		Transition* transition = pair.second;

		if (!transition)
			continue;

		if (transition->CanTransition())
		{
			return pair.first;
		}
	}

	return EState::End;
}

bool BaseState::CheckTransition()
{
	EState nextState = EState::End;
	if ((nextState = CanTransition()) != EState::End)
	{
		return StateManager::GetInstance().ChangeState(nextState);
	}
	return false;
}
