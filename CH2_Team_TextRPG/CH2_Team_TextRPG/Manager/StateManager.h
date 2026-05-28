#pragma once
#include "Core/State.h"
#include "Enum/EState.h"

class StateManager
{
	friend BaseState;
	
private:
	StateManager() {};
public:
	virtual ~StateManager();

	static StateManager& GetInstance();

	bool Initialize();
	void Process();

	bool ChangeState(EState InNextState);
private:
	bool InitializeStates();

	template<typename T>
	void AddState(EState InState);
private:
	BaseState* CurrentState = nullptr;
	std::map<EState, BaseState*> States;

public:
	const BaseState* GetCurrnetState() { return CurrentState; }
};

template<typename T>
inline void StateManager::AddState(EState InState)
{
	T* menuState = new T();

	if (menuState)
	{
		States.emplace(InState, menuState);
	}

	return;
}
