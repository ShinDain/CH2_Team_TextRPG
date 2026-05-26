#include "pch.h"
#include "ConsoleRenderer.h"
#include "Manager/InputManager.h"
#include "UI/ConsoleUtil.h"

#include <windows.h>

void ConsoleRenderer::SetupConsoleSize(int Width, int Height)
{
    ConsoleUtil::SetupConsoleCharacterSize(Width, Height);
}

void ConsoleRenderer::SetupLargeConsole()
{
    ConsoleUtil::SetupLargeConsole();
}

void ConsoleRenderer::WaitForConsoleReady()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    system("cls");

    std::cout << "============================================================\n";
    std::cout << "                    Text RPG 실행 준비\n";
    std::cout << "============================================================\n\n";
    std::cout << "이 게임은 큰 ASCII 그래픽을 사용합니다.\n\n";
    std::cout << "콘솔 창 크기를 자동으로 설정했습니다.\n";
    std::cout << "아무 키나 누르면 게임이 시작됩니다.\n\n";
    std::cout << "설정 화면 크기: 가로 210, 세로 65\n\n";
    std::cout << "계속하려면 아무 키나 누르세요...";

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    GInput.WaitForKey();

    system("cls");
}

void ConsoleRenderer::ClearScreen()
{
    system("cls");
}

void ConsoleRenderer::SetCursorPosition(int X, int Y)
{
    COORD Position;
    Position.X = static_cast<SHORT>(X);
    Position.Y = static_cast<SHORT>(Y);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}

void ConsoleRenderer::DrawString(int X, int Y, const std::string& Text)
{
    SetCursorPosition(X, Y);

    GInput << Text;
}

void ConsoleRenderer::DrawBox(int X, int Y, int Width, int Height)
{
    DrawString(X, Y, "+");

    for (int i = 0; i < Width - 2; i++)
    {
        GInput << "-";
    }

    GInput << "+";

    for (int Row = 1; Row < Height - 1; Row++)
    {
        DrawString(X, Y + Row, "|");
        DrawString(X + Width - 1, Y + Row, "|");
    }

    DrawString(X, Y + Height - 1, "+");

    for (int i = 0; i < Width - 2; i++)
    {
        GInput << "-";
    }

    GInput << "+";
}

void ConsoleRenderer::DrawLines(int X, int Y, const std::vector<std::string>& Lines)
{
    for (int i = 0; i < static_cast<int>(Lines.size()); i++)
    {
        DrawString(X, Y + i, Lines[i]);
    }
}
