#include "pch.h"
#include "GameInstance.h"

GameInstance::GameInstance()
{
	IsRunning = false;
}

GameInstance::~GameInstance()
{
}

GameInstance& GameInstance::GetInstance()
{
	static GameInstance Instance;

	return Instance;
}

bool GameInstance::Initialize()
{
	IsRunning = true;

	return true;
}

void GameInstance::RunLoop()
{
	while (IsRunning)
	{
		cout << "Press Input (Exit = 0) : ";

		int input = -1;
		cin >> input;

		if (input == 0)
		{
			IsRunning = false;
		}
	}
}

void GameInstance::ShutDown()
{
}
