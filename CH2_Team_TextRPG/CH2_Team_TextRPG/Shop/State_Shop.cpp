#include "pch.h"
#include "State_Shop.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

State_Shop::State_Shop()
{
	Name = "Shop";
}

void State_Shop::Enter()
{
	GLog.AddLog("상점에 입장했습니다.");
}

void State_Shop::Process()
{
	ConsoleRenderer::ClearScreen();
	ConsoleUtil::HideCursor();

	ConsoleRenderer::DrawBox(55, 10, 100, 22);
	ConsoleRenderer::SetCursorPosition(96, 13);
	GInput << "상점";
	ConsoleRenderer::SetCursorPosition(68, 17);
	GInput << "상점 로직은 준비 중입니다.";
	ConsoleRenderer::SetCursorPosition(68, 20);
	GInput << "0. 맵으로 돌아가기";
	ConsoleRenderer::SetCursorPosition(68, 28);
	GInput << "입력 >> ";

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		GLog.AddLog("잘못된 입력입니다.");
		return;
	}

	if (Input == 0)
	{
		StateManager::GetInstance().ChangeState(EState::Map);
	}
}

void State_Shop::Exit()
{
	GLog.AddLog("상점을 떠났습니다.");
}
