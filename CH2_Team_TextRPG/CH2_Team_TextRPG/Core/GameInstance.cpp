#include "pch.h"
#include "GameInstance.h"
#include "Manager/ObjectManager.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "Data/DataLoader.h"
#include "Character/Player/Player.h"

using namespace std;

GameInstance::GameInstance() :
	GameInputManager(nullptr),
	MainPlayer(nullptr)
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
	Result = InitializeDataTable();
	Result = InitializeManager();

	MainPlayer = CreateObject<Player>();

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

Player* GameInstance::GetMainPlayer() const
{
	return MainPlayer;
}

void GameInstance::SetBattleStartData(const BattleStartData& InBattleStartData)
{
	CurrentBattleStartData = InBattleStartData;
	bHasBattleStartData = true;
}

const BattleStartData* GameInstance::GetBattleStartData() const
{
	return bHasBattleStartData ? &CurrentBattleStartData : nullptr;
}

void GameInstance::ClearBattleStartData()
{
	CurrentBattleStartData = {};
	bHasBattleStartData = false;
}

void GameInstance::SetResultType(EResultType Type)
{
	ResultType = Type;
}

EResultType GameInstance::GetResultType() const
{
	return ResultType;
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
