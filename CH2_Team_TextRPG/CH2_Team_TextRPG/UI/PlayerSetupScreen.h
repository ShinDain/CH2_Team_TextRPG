#pragma once

#include "UI/ConsoleUtil.h"

class PlayerSetupScreen
{
public:
	static void DrawPlayerNameInput();
	static void DrawPlayerNameError();
	static void DrawSelectJobNumber();
	static void DrawSelectJobError(const std::string& Message);
	static void DrawPlayerJobSelect();
	static void DrawLoadScreen();
	static void DrawStatusMessage(const std::string& Msg, ConsoleColor Color = ConsoleColor::White);
};
