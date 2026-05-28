#include "pch.h"
#include "UI/PlayerSetupScreen.h"
#include "Manager/InputManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

namespace
{
struct JobSelectViewData
{
	const char* Name;
	const char* Description;
	const char* Stats;
};

const JobSelectViewData JobViews[] =
{
	{
		"전사",
		"높은 체력과 방어력을 가진 근접 직업입니다.",
		"HP 220 / MP 80 / ATK 35 / DEF 8 / SPD 8"
	},
	{
		"마법사",
		"높은 마나와 강력한 마법 공격을 사용하는 직업입니다.",
		"HP 150 / MP 180 / ATK 25 / DEF 3 / SPD 7"
	},
	{
		"도적",
		"빠른 속도와 연속 공격에 특화된 직업입니다.",
		"HP 170 / MP 110 / ATK 30 / DEF 5 / SPD 14"
	}
};
}

void PlayerSetupScreen::DrawPlayerNameInput()
{
	ConsoleUtil::HideCursor();
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(45, 5, 120, 40);

	ConsoleRenderer::SetCursorPosition(47, 7);
	GInput << "이름을 입력하세요: ";

	ConsoleRenderer::SetCursorPosition(47, 9);
	
}

void PlayerSetupScreen::DrawPlayerNameError()
{
	ConsoleUtil::HideCursor();
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(45, 5, 120, 40);

	ConsoleRenderer::SetCursorPosition(47, 7);
	ConsoleUtil::WriteColored("잘못 입력하였습니다!", ConsoleColor::Red);
}

void PlayerSetupScreen::DrawSelectJobNumber()
{
	// 입력 영역(이전 잘못된 숫자 잔존 가능) 부분 클리어
	ConsoleUtil::ClearArea(52, 37, 60, 1);

	ConsoleRenderer::SetCursorPosition(52, 37);
	ConsoleUtil::WriteColored("직업 번호 입력 >> ", ConsoleColor::White);
	ConsoleUtil::ShowCursor();
}

void PlayerSetupScreen::DrawSelectJobError(const std::string& Message)
{
	// 에러 메시지 영역 부분 클리어 후 빨간 글씨로 표시
	ConsoleUtil::ClearArea(52, 39, 110, 1);
	ConsoleRenderer::SetCursorPosition(52, 39);
	ConsoleUtil::WriteColored(Message, ConsoleColor::Red);
}

void PlayerSetupScreen::DrawPlayerJobSelect()
{
	ConsoleUtil::HideCursor();
	ConsoleRenderer::ClearScreen();
	ConsoleRenderer::DrawBox(45, 5, 120, 40);

	ConsoleRenderer::SetCursorPosition(94, 8);
	ConsoleUtil::WriteColored("직업 선택", ConsoleColor::Cyan);

	const int StartX = 52;
	const int StartY = 13;
	const int GapY = 7;

	for (int i = 0; i < 3; i++)
	{
		const JobSelectViewData& Job = JobViews[i];
		const int Y = StartY + (i * GapY);

		ConsoleRenderer::SetCursorPosition(StartX, Y);
		GInput << i + 1 << ". " << Job.Name;
		ConsoleRenderer::SetCursorPosition(StartX, Y + 1);
		GInput << Job.Description;
		ConsoleRenderer::SetCursorPosition(StartX, Y + 3);
		GInput << Job.Stats;
	}

	ConsoleRenderer::SetCursorPosition(52, 35);
	ConsoleUtil::WriteColored("0. 시작 메뉴로 돌아가기", ConsoleColor::DarkGray);
}
