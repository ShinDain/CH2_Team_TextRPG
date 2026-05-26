#include "pch.h"
#include "GameInstance.h"
#include "Manager/ObjectManager.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "Data/DataLoader.h"


using namespace std;

GameInstance::GameInstance() :
	GameInputManager(nullptr)
{
	IsRunning = false;
}

GameInstance::~GameInstance()
{
	delete GameInputManager;
	GameInputManager = nullptr;
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
	Result = InitializeDataTable();

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
	Log.AddLog("게임이 종료되었습니다.");
}

void GameInstance::Quit()
{
	IsRunning = false;
}

MapManager& GameInstance::GetMapManager()
{
	return Map;
}

LogManager& GameInstance::GetLogManager()
{
	return Log;
}

bool GameInstance::InitializeManager()
{
	if (GameInputManager == nullptr)
	{
		GameInputManager = new InputManager();
	}

	Map.GenerateFixedMap();

	Log.AddLog("게임을 시작했습니다.");
	Log.AddLog("던전 지도가 생성되었습니다.");

	StateManager::GetInstance().Initialize();

	return true;
}

bool GameInstance::InitializeDataTable()
{
	DataLoader::LoadInitialGameData();

	return true;
}
