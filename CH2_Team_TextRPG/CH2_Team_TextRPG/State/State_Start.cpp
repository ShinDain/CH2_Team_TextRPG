#include "pch.h"
#include "State_Start.h"
#include "Manager/InputManager.h"
#include "UI/BattleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "Core/GameInstance.h"
#include "Core/GameProgress.h"
#include "UI/GameScreen.h"
#include "Character/Player/Player.h"
#include <windows.h>

namespace
{
	bool RunBattleRendererTest(GameInstance& Instance)
	{
		BattleRenderer battleRenderer;
		battleRenderer.DrawBattleScreen();

		battleRenderer.ClearMonsters();
		battleRenderer.AddMonster("goblin", 65, 6);
		battleRenderer.AddMonster("goblin", 120, 6);

		battleRenderer.DrawAllMonsterIdle();
		Sleep(700);

		battleRenderer.PlayMonsterAttackAnimation(0);
		Sleep(500);

		battleRenderer.PlayMonsterHitAnimation(1);
		Sleep(500);

		battleRenderer.DrawAllMonsterIdle();

		ConsoleUtil::SetCursorPosition(32, 31);
		GInput << "전투 테스트 종료: 0 입력 >> ";

		int Input = 0;
		std::cin >> Input;

		if (Input == 0)
		{
			Instance.Quit();
			return true;
		}

		return false;
	}
}

State_Start::State_Start()
{

}

void State_Start::Enter()
{
	GameInstance::GetInstance().GetLogManager().AddLog("맵 화면에 진입했습니다.");
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	ConsoleUtil::HideCursor();

	GameScreen::DrawMainScreen(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);

	if (Instance.GetMapManager().IsBossNode())
	{
		if (RunBattleRendererTest(Instance))
		{
			return;
		}

		GameProgress::HandleCurrentNodeEvent(
			Instance.GetMapManager(),
			Instance.GetLogManager()
		);

		GameProgress::EndGame(Instance.GetLogManager());
		Instance.Quit();
		return;
	}

	GameProgress::HandleNodeSelection(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);

	if (RunBattleRendererTest(Instance))
	{
		return;
	}

	GameProgress::HandleCurrentNodeEvent(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);
}

void State_Start::Exit()
{
}
