#include "pch.h"
#include "State_Start.h"
#include "Enum/EState.h"
#include "Core/Condition.h"

using namespace std;

State_Start::State_Start()
{
	AddTransition<AlwaysTrueCondition>(EState::Start);
}

void State_Start::Enter()
{
	cout << "StartState Enter" << endl;
}

void State_Start::Process()
{
	cout << "StartState Process" << endl;
	cout << "input (exit = 0) : ";

	int input = 0;
	cin >> input;

	if (input == 0)
		GameInstance::GetInstance().Quit();
}

void State_Start::Exit()
{
	cout << "StartState Exit" << endl;
}
