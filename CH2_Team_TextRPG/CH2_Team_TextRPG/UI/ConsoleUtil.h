#pragma once

#include <string>

enum class ConsoleColor
{
    Black = 0,
    DarkBlue = 1,
    DarkGreen = 2,
    DarkCyan = 3,
    DarkRed = 4,
    DarkMagenta = 5,
    DarkYellow = 6,
    Gray = 7,
    DarkGray = 8,
    Blue = 9,
    Green = 10,
    Cyan = 11,
    Red = 12,
    Magenta = 13,
    Yellow = 14,
    White = 15
};

class ConsoleUtil
{
public:
    static void SetupConsoleFont();
    static void SetupConsoleCharacterSize(int columns, int rows);
    static void SetupConsoleWindowPosition();
    static void DisableConsoleResize();
    static void SetupLargeConsole();
    static void PrintConsoleSizeDebug();
    static void SetCursorPosition(int x, int y);
    static void HideCursor();
    static void ClearArea(int x, int y, int width, int height);
    static void SetTextColor(ConsoleColor color);
    static void ResetTextColor();
    static void WriteColored(const std::string& text, ConsoleColor color);
};
