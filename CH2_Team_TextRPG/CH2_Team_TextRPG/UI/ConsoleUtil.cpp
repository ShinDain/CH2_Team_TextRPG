#include "pch.h"
#include "ConsoleUtil.h"
#include "Manager/InputManager.h"

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
        GInput << blank;
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
    GInput << text;
    ResetTextColor();
}

void ConsoleUtil::WriteGauge(
    int current,
    int max,
    int width,
    ConsoleColor fillColor,
    ConsoleColor emptyColor
)
{
    if (width <= 0)
    {
        return;
    }

    current = current < 0 ? 0 : current;
    max = max < 0 ? 0 : max;

    const int ClampedCurrent = max > 0
        ? (current > max ? max : current)
        : 0;
    const int FilledWidth = max > 0
        ? (ClampedCurrent * width + max / 2) / max
        : 0;

    SetTextColor(fillColor);
    for (int i = 0; i < FilledWidth; i++)
    {
        GInput << "■";
    }

    SetTextColor(emptyColor);
    for (int i = FilledWidth; i < width; i++)
    {
        GInput << "□";
    }

    ResetTextColor();
}
