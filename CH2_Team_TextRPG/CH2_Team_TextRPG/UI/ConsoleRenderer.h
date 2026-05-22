#pragma once

#include <string>
#include <vector>

class ConsoleRenderer
{
public:
    static void ClearScreen();

    static void DrawString(int X, int Y, const std::string& Text);
    static void DrawBox(int X, int Y, int Width, int Height);
    static void DrawLines(int X, int Y, const std::vector<std::string>& Lines);
};