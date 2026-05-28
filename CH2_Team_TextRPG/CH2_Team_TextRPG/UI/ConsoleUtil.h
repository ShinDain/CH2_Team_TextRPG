#pragma once

#include <string>
#include <windows.h>

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
    static void SetCursorPosition(int x, int y);
    static void HideCursor();
    static void ClearArea(int x, int y, int width, int height);
    static void SetTextColor(ConsoleColor color);
    static void ResetTextColor();
    static void WriteColored(const std::string& text, ConsoleColor color);
    static void WriteGauge(
        int current,
        int max,
        int width,
        ConsoleColor fillColor,
        ConsoleColor emptyColor = ConsoleColor::DarkGray
    );
};
