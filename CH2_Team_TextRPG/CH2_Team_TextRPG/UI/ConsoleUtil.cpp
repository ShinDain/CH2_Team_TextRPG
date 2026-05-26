#include "pch.h"
#include "ConsoleUtil.h"

#include <iostream>
#include <string>
#include <windows.h>

void ConsoleUtil::SetCursorPosition(int x, int y)
{
    COORD pos;
    pos.X = static_cast<SHORT>(x);
    pos.Y = static_cast<SHORT>(y);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ConsoleUtil::HideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);

    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void ConsoleUtil::ClearArea(int x, int y, int width, int height)
{
    std::string blank(width, ' ');

    for (int i = 0; i < height; i++)
    {
        SetCursorPosition(x, y + i);
        std::cout << blank;
    }
}

void ConsoleUtil::SetTextColor(ConsoleColor color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        static_cast<WORD>(color)
    );
}

void ConsoleUtil::ResetTextColor()
{
    SetTextColor(ConsoleColor::Gray);
}

void ConsoleUtil::WriteColored(const std::string& text, ConsoleColor color)
{
    SetTextColor(color);
    std::cout << text;
    ResetTextColor();
}
