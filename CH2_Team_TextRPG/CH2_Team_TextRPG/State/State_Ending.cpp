#include "pch.h"
#include "State_Ending.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

namespace
{
std::string GetEndingTitle(EEndingType EndingType)
{
	return EndingType == EEndingType::Clear ? "게임 클리어" : "게임 오버";
}

ConsoleColor GetEndingTitleColor(EEndingType EndingType)
{
	return EndingType == EEndingType::Clear ? ConsoleColor::Yellow : ConsoleColor::Red;
}
}

State_Ending::State_Ending()
{
	Name = "Ending";
}

void State_Ending::Enter()
{
	GameInstance& Instance = GameInstance::GetInstance();

	if (Instance.GetEndingType() == EEndingType::Clear)
	{
		Instance.GetLogManager().AddLog("게임을 클리어했습니다.");
	}
	else
	{
		Instance.GetLogManager().AddLog("플레이어가 쓰러졌습니다.");
		Instance.GetLogManager().AddLog("게임 오버입니다.");
	}
}

void State_Ending::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();
	const EEndingType EndingType = Instance.GetEndingType();

	ConsoleRenderer::ClearScreen();
	ConsoleUtil::HideCursor();

	ConsoleRenderer::DrawBox(55, 10, 100, 24);
	ConsoleRenderer::SetCursorPosition(94, 13);
	ConsoleUtil::WriteColored(GetEndingTitle(EndingType), GetEndingTitleColor(EndingType));

	std::vector<std::string> RecentLogs = Instance.GetLogManager().GetRecentLogs(5);
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
		Instance.Quit();
	}
	else if (Input == 1)
	{
		StateManager::GetInstance().ChangeState(EState::Start);
	}
}

void State_Ending::Exit()
{
}
