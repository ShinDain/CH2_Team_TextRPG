#pragma once

#include <string>

class PlayerSetupScreen
{
public:
	static void DrawPlayerNameInput();
	static void DrawPlayerNameError();
	static void DrawSelectJobNumber();
	static void DrawSelectJobError(const std::string& Message);
	static void DrawPlayerJobSelect();

};
