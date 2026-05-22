#pragma once
#include "Core/State.h"
#include "Enum/EState.h"

class StateManager
{
private:
	StateManager() {};
public:
	virtual ~StateManager();

	static StateManager& GetInstance();

	bool Initialize();
	void Process();

	bool ChangeState(EState nextState);
private:
	bool InitializeStates();

	template<typename T>
	void AddState(EState id);
private:
	BaseState* CurrentState;
	std::map<EState, BaseState*> States;

public:
	const BaseState* GetCurrnetState() { return CurrentState; }
};

template<typename T>
inline void StateManager::AddState(EState id)
{
	T* menuState = new T();

	if (menuState)
	{
		States.emplace(id, menuState);
	}

	return;
}
