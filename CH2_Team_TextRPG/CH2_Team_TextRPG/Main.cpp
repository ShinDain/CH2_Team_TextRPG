#include "pch.h"
#include "Core/GameInstance.h"
#include "UI/ConsoleRenderer.h"
#include <cstdlib>

int main()
{
	ConsoleRenderer::WaitForConsoleReady();

	GameInstance& Instance = GameInstance::GetInstance();

	if (Instance.Initialize())
	{
		Instance.RunLoop();
	}

	Instance.ShutDown();

	return 0;
}
