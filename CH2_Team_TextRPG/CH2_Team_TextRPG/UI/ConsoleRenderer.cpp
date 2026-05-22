#include "pch.h"
#include "ConsoleRenderer.h"

#include <iostream>
#include <windows.h>

void ConsoleRenderer::ClearScreen()
{
    system("cls");
}

void ConsoleRenderer::DrawString(int X, int Y, const std::string& Text)
{
    COORD Position;
    Position.X = static_cast<SHORT>(X);
    Position.Y = static_cast<SHORT>(Y);

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);

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