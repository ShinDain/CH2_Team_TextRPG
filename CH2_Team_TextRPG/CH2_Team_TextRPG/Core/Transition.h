#pragma once
#include "Condition.h"
#include "Enum/EState.h"

class Transition
{
public:
	Transition() = delete;
	Transition(ICondition* InCondition, EState InNextState);
	virtual ~Transition();

	void InitTransition();

	EState GetNextEState() { return NextState; }
	bool CanTransition() const;

	void Notify() { Condition->OnNotify(); }
	ICondition* GetCondition() { return Condition; }
protected:
	ICondition* Condition;
	EState NextState;
};