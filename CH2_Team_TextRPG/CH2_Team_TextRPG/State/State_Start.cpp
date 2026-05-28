#include "pch.h"
#include "State_Start.h"
#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

State_Start::State_Start()
{
	Name = "Start";
}

void State_Start::Enter()
{
	GameInstance::GetInstance().GetLogManager().AddLog("시작 메뉴에 진입했습니다.");
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	ConsoleUtil::HideCursor();
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(65, 12, 80, 18);
	ConsoleRenderer::SetCursorPosition(96, 15);
	GInput << "TEXT RPG";
	ConsoleRenderer::SetCursorPosition(88, 19);
	GInput << "1. 새 게임";
	ConsoleRenderer::SetCursorPosition(88, 21);
	GInput << "2. 불러오기";
	ConsoleRenderer::SetCursorPosition(88, 23);
	GInput << "0. 종료";
	ConsoleRenderer::SetCursorPosition(88, 27);
	GInput << "입력 >> ";

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		Instance.GetLogManager().AddLog("잘못된 입력입니다.");
		return;
	}

	switch (Input)
	{
	case 1:
		Instance.GetMapManager().GenerateFixedMap();
		if (Player* MainPlayer = GameInstance::GetInstance().GetMainPlayer())
		{
			MainPlayer->RestoreAll();
		}
		Instance.GetLogManager().AddLog("새 게임을 시작합니다.");
		StateManager::GetInstance().ChangeState(EState::Map);
		break;
	case 2:
		Instance.GetLogManager().AddLog("저장 데이터 로드는 임시로 새 게임 흐름을 사용합니다.");
		StateManager::GetInstance().ChangeState(EState::Map);
		break;
	case 0:
		Instance.Quit();
		break;
	default:
		Instance.GetLogManager().AddLog("메뉴 번호를 다시 선택해주세요.");
		break;
	}
}

void State_Start::Exit()
{
}
