#include "pch.h"
#include "GameInstance.h"
#include "Manager/ObjectManager.h"
#include "Manager/StateManager.h"

using namespace std;

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
	bool Result = true;
	Result = InitializeManager();

	IsRunning = true;
	return Result;
}

void GameInstance::RunLoop()
{
	while (IsRunning)
	{
		StateManager::GetInstance().Process();
	}
}

void GameInstance::ShutDown()
{
}

void GameInstance::Quit()
{
	IsRunning = false;
}

bool GameInstance::InitializeManager()
{
	StateManager::GetInstance().Initialize();

	return true;
}
