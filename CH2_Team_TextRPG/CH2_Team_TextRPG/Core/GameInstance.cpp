#include "pch.h"
#include "GameInstance.h"
#include "GameProgress.h"
#include "../UI/GameScreen.h"

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

	Map.GenerateFixedMap();

	Log.AddLog("게임을 시작했습니다.");
	Log.AddLog("던전 지도가 생성되었습니다.");

	return true;
}

void GameInstance::RunLoop()
{
	while (IsRunning)
	{
		GameScreen::DrawMainScreen(Map, Log);

		if (Map.IsBossNode())
		{
			GameProgress::HandleCurrentNodeEvent(Map, Log);
			GameProgress::EndGame(Log);
			IsRunning = false;
			break;
		}

		GameProgress::HandleNodeSelection(Map, Log);
		GameProgress::HandleCurrentNodeEvent(Map, Log);
	}
}

void GameInstance::ShutDown()
{
	Log.AddLog("게임이 종료되었습니다.");
}