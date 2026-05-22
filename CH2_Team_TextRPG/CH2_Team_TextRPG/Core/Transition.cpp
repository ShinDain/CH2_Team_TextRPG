#include "pch.h"
#include "Transition.h"
#include "Condition.h"

Transition::Transition(ICondition* InCondition, EState InNextState)
	: Condition(InCondition), NextState(InNextState)
{
}

Transition::~Transition()
{
	delete Condition;
}

void Transition::InitTransition()
{
	Condition->Init();
}

bool Transition::CanTransition() const
{
	if (!Condition)
		return false;

	return Condition->Check();
}
