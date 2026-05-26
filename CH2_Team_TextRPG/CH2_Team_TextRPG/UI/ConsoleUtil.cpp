#include "pch.h"
#include "ConsoleUtil.h"
#include "Manager/InputManager.h"

#include <windows.h>

namespace
{
    constexpr int ConsoleColumns = 210;
    constexpr int ConsoleRows = 65;

    constexpr int ConsoleWindowX = 0;
    constexpr int ConsoleWindowY = 0;

    constexpr int DesiredWindowPixelWidth = 1600;
    constexpr int DesiredWindowPixelHeight = 900;

    constexpr int ConsoleFontHeight = 12;

    void PrintDebugMessage(const char* message)
    {
#ifdef _DEBUG
        std::cout << message << "\n";
#else
        (void)message;
#endif
    }
}

void ConsoleUtil::SetupConsoleFont()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (consoleHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    CONSOLE_FONT_INFOEX fontInfo = {};
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    fontInfo.dwFontSize.Y = ConsoleFontHeight;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    if (!SetCurrentConsoleFontEx(consoleHandle, FALSE, &fontInfo))
    {
        PrintDebugMessage("SetCurrentConsoleFontEx failed.");
    }
}

void ConsoleUtil::SetupConsoleCharacterSize(int columns, int rows)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (consoleHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    SetConsoleTitle(TEXT("Text RPG"));

    COORD largestSize = GetLargestConsoleWindowSize(consoleHandle);

    if (largestSize.X < columns || largestSize.Y < rows)
    {
#ifdef _DEBUG
        std::cout << "Warning: Requested console size "
            << columns << " x " << rows
            << " exceeds the largest available console size.\n";
#endif
    }

    SMALL_RECT tempRect = { 0, 0, 1, 1 };
    if (!SetConsoleWindowInfo(consoleHandle, TRUE, &tempRect))
    {
        PrintDebugMessage("SetConsoleWindowInfo failed while shrinking console window.");
    }

    COORD bufferSize;
    bufferSize.X = static_cast<SHORT>(columns);
    bufferSize.Y = static_cast<SHORT>(rows);
    if (!SetConsoleScreenBufferSize(consoleHandle, bufferSize))
    {
        PrintDebugMessage("SetConsoleScreenBufferSize failed.");
    }

    SMALL_RECT windowRect;
    windowRect.Left = 0;
    windowRect.Top = 0;
    windowRect.Right = static_cast<SHORT>(columns - 1);
    windowRect.Bottom = static_cast<SHORT>(rows - 1);
    if (!SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect))
    {
        PrintDebugMessage("SetConsoleWindowInfo failed while applying console window size.");
    }
}

void ConsoleUtil::SetupConsoleWindowPosition()
{
    HWND consoleWindow = GetConsoleWindow();

    if (consoleWindow == nullptr)
    {
        return;
    }

    const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    const int windowWidth = (DesiredWindowPixelWidth < screenWidth) ? DesiredWindowPixelWidth : screenWidth;
    const int windowHeight = (DesiredWindowPixelHeight < screenHeight) ? DesiredWindowPixelHeight : screenHeight;

    if (!SetWindowPos(
        consoleWindow,
        nullptr,
        ConsoleWindowX,
        ConsoleWindowY,
        windowWidth,
        windowHeight,
        SWP_NOZORDER | SWP_NOOWNERZORDER
    ))
    {
        PrintDebugMessage("SetWindowPos failed.");
    }
}

void ConsoleUtil::DisableConsoleResize()
{
    HWND consoleWindow = GetConsoleWindow();

    if (consoleWindow == nullptr)
    {
        return;
    }

    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~WS_SIZEBOX;
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(consoleWindow, GWL_STYLE, style);

    SetWindowPos(
        consoleWindow,
        nullptr,
        0,
        0,
        0,
        0,
        SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_FRAMECHANGED
    );
}

void ConsoleUtil::PrintConsoleSizeDebug()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if (consoleHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO bufferInfo = {};

    if (!GetConsoleScreenBufferInfo(consoleHandle, &bufferInfo))
    {
        return;
    }

    const int windowWidth = bufferInfo.srWindow.Right - bufferInfo.srWindow.Left + 1;
    const int windowHeight = bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top + 1;
    COORD largestSize = GetLargestConsoleWindowSize(consoleHandle);

    std::cout << "Console Window Size: " << windowWidth << " x " << windowHeight << "\n";
    std::cout << "Console Buffer Size: " << bufferInfo.dwSize.X << " x " << bufferInfo.dwSize.Y << "\n";
    std::cout << "Largest Console Window Size: " << largestSize.X << " x " << largestSize.Y << "\n";
}

void ConsoleUtil::SetupLargeConsole()
{
    SetupConsoleFont();
    SetupConsoleWindowPosition();
    SetupConsoleCharacterSize(ConsoleColumns, ConsoleRows);
    DisableConsoleResize();
    HideCursor();
}

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

    if (consoleHandle == INVALID_HANDLE_VALUE)
    {
        return;
    }

    CONSOLE_CURSOR_INFO cursorInfo = {};

    if (!GetConsoleCursorInfo(consoleHandle, &cursorInfo))
    {
        return;
    }

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
