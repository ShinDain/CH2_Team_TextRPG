#include "pch.h"
#include "StateManager.h"
#include "State/State_Entry.h"
#include "State/State_Start.h"
#include "State/State_Map.h"
#include "Combat/State_Battle.h"
#include "Shop/State_Shop.h"
#include "State/State_Result.h"

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

	ChangeState(EState::Entry);

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
	else
	{
		if (CurrentState)
		{
			CurrentState->Exit();
			CurrentState->InitTransitions();
			CurrentState->Enter();
		}
	}
	
	return false;
}

bool StateManager::InitializeStates()
{
	AddState<State_Entry>(EState::Entry);
	AddState<State_Start>(EState::Start);
	AddState<State_Map>(EState::Map);
	AddState<State_Battle>(EState::Combat);
	AddState<State_Shop>(EState::Shop);
	AddState<State_Result>(EState::Result);

	return true;
}
