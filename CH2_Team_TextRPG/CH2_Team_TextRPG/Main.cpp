#include "pch.h"
#include "Core/GameInstance.h"

int main()
{
	GameInstance& Instance = GameInstance::GetInstance();

	if (Instance.Initialize())
	{
		Instance.RunLoop();
	}

	Instance.ShutDown();
}
