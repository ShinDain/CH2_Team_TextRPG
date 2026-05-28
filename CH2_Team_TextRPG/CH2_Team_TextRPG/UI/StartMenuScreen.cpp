#include "pch.h"
#include "UI/StartMenuScreen.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "Manager/InputManager.h"

void StartMenuScreen::Draw()
{
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
}
