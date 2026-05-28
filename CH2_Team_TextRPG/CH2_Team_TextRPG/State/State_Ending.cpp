#include "pch.h"
#include "State_Ending.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

State_Ending::State_Ending()
{
	Name = "Ending";
}

void State_Ending::Enter()
{
	GLog.AddLog("게임을 클리어했습니다.");
}

void State_Ending::Process()
{
	ConsoleRenderer::ClearScreen();
	ConsoleUtil::HideCursor();

	ConsoleRenderer::DrawBox(55, 10, 100, 24);
	ConsoleRenderer::SetCursorPosition(94, 13);
	GInput << "게임 클리어";

	std::vector<std::string> RecentLogs = GLog.GetRecentLogs(5);
	for (int i = 0; i < static_cast<int>(RecentLogs.size()); i++)
	{
		ConsoleRenderer::SetCursorPosition(62, 17 + i);
		GInput << "> " << RecentLogs[i];
	}

	ConsoleRenderer::SetCursorPosition(78, 28);
	GInput << "1. 시작 메뉴로";
	ConsoleRenderer::SetCursorPosition(78, 30);
	GInput << "0. 종료";
	ConsoleRenderer::SetCursorPosition(78, 32);
	GInput << "입력 >> ";

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		return;
	}

	if (Input == 0)
	{
		GameInstance::GetInstance().Quit();
	}
	else if (Input == 1)
	{
		StateManager::GetInstance().ChangeState(EState::Start);
	}
}

void State_Ending::Exit()
{
}
