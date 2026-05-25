#pragma once

#include <windows.h>

class ConsoleUtil
{
public:
    static void SetCursorPosition(int x, int y);
    static void HideCursor();
    static void ClearArea(int x, int y, int width, int height);
};