#include "pch.h"
#include "Core/GameInstance.h"

#include <windows.h>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	GameInstance& Instance = GameInstance::GetInstance();

	if (Instance.Initialize())
	{
		Instance.RunLoop();
	}

	Instance.ShutDown();

	return 0;
}