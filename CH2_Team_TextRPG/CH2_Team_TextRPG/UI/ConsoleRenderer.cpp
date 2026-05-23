#include "pch.h"
#include "ConsoleRenderer.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

void ConsoleRenderer::SetupConsoleSize(int Width, int Height)
{
    std::string Command = "mode con: cols=" +
        std::to_string(Width) +
        " lines=" +
        std::to_string(Height);

    system(Command.c_str());
}

void ConsoleRenderer::SetupLargeConsole()
{
    SetupConsoleSize(210, 65);
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
    std::cout << "콘솔 창을 전체화면 또는 최대한 크게 키워주세요.\n";
    std::cout << "창 크기를 키운 뒤 아무 키나 누르면 게임이 시작됩니다.\n\n";
    std::cout << "권장 화면 크기: 가로 120 이상, 세로 50 이상\n\n";
    std::cout << "계속하려면 아무 키나 누르세요...";

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();

    SetupLargeConsole();

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

    std::cout << Text;
}

void ConsoleRenderer::DrawBox(int X, int Y, int Width, int Height)
{
    DrawString(X, Y, "+");

    for (int i = 0; i < Width - 2; i++)
    {
        std::cout << "-";
    }

    std::cout << "+";

    for (int Row = 1; Row < Height - 1; Row++)
    {
        DrawString(X, Y + Row, "|");
        DrawString(X + Width - 1, Y + Row, "|");
    }

    DrawString(X, Y + Height - 1, "+");

    for (int i = 0; i < Width - 2; i++)
    {
        std::cout << "-";
    }

    std::cout << "+";
}

void ConsoleRenderer::DrawLines(int X, int Y, const std::vector<std::string>& Lines)
{
    for (int i = 0; i < static_cast<int>(Lines.size()); i++)
    {
        DrawString(X, Y + i, Lines[i]);
    }
}
