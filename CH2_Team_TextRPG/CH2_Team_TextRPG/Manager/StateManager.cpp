#include "pch.h"
#include "StateManager.h"
#include "State/State_Start.h"
#include "Shop/State_Shop.h"

StateManager& StateManager::GetInstance()
{
	static StateManager Instance;
	return Instance;
}

StateManager::~StateManager()
{
	for (auto& pair : States)
	{
		delete pair.second;
	}

	States.clear();
	CurrentState = nullptr;
}

bool StateManager::Initialize()
{
	if (!InitializeStates())
		return false;

	ChangeState(EState::Start);

	return true;
}

void StateManager::Process()
{
	if (CurrentState == nullptr)
		return;

	CurrentState->Process();
	CurrentState->CheckTransition();
}

bool StateManager::ChangeState(EState InNextState)
{
	if (States.find(InNextState) != States.end())
	{
		if (CurrentState)
			CurrentState->Exit();
		CurrentState = States[InNextState];
		CurrentState->InitTransitions();
		CurrentState->Enter();

		return true;
	}

	return false;
}

bool StateManager::InitializeStates()
{
	AddState<State_Start>(EState::Start);

	AddState<State_Shop>(EState::Shop);

	return true;
}
