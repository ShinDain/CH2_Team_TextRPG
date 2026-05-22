#pragma once

#include "Transition.h"
#include "Enum/EState.h"

class StateManager;

class BaseState 
{
	friend StateManager;

protected:
	BaseState();
public:
	virtual ~BaseState();

	EState CanTransition() const;
	bool CheckTransition();
protected:
	virtual void Enter() {};
	virtual void Process() {};
	virtual void Exit() {};

	void InitTransition();

	template<typename T>
	void AddTransition(EState InState);
protected:
	std::string Name;
	std::map<EState, Transition*> Transitions;
public:
	std::string GetName() { return Name; }
};

template<typename T>
inline void BaseState::AddTransition(EState InState)
{
	EState destState = InState;
	T* condition = new T();
	Transition* transition = new Transition(condition, destState);
	transition->InitTransition();
	Transitions.emplace(destState, transition);
}
