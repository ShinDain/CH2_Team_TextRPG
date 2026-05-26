#include "pch.h"
#include "Core/GameInstance.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"
#include <cstdlib>

int main()
{
	ConsoleUtil::SetupLargeConsole();

	GameInstance& Instance = GameInstance::GetInstance();

	if (Instance.Initialize())
	{
		ConsoleRenderer::WaitForConsoleReady();
		Instance.RunLoop();
	}

	Instance.ShutDown();

	return 0;
}
