#pragma once

#include <string>
#include <vector>

class ConsoleRenderer
{
public:
    static void SetupConsoleSize(int Width, int Height);
    static void SetupLargeConsole();
    static void WaitForConsoleReady();
    static void ClearScreen();

    static void SetCursorPosition(int X, int Y);
    static void DrawString(int X, int Y, const std::string& Text);
    static void DrawBox(int X, int Y, int Width, int Height);
    static void DrawLines(int X, int Y, const std::vector<std::string>& Lines);
};
