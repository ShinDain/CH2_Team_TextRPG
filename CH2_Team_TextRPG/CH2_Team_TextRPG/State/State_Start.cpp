#include "pch.h"
#include "State_Start.h"

#include "Enum/EState.h"
#include "Core/Condition.h"
#include "Core/GameInstance.h"
#include "Core/GameProgress.h"
#include "UI/GameScreen.h"

using namespace std;

State_Start::State_Start()
{
	// 지금은 StartState 안에서 바로 맵 화면을 실행할 것이므로
	// 자동 전환은 사용하지 않습니다.
	// AddTransition<AlwaysTrueCondition>(EState::Start);
}

void State_Start::Enter()
{
	GameInstance::GetInstance().GetLogManager().AddLog("맵 화면에 진입했습니다.");
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	GameScreen::DrawMainScreen(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);

	if (Instance.GetMapManager().IsBossNode())
	{
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

	GameProgress::HandleCurrentNodeEvent(
		Instance.GetMapManager(),
		Instance.GetLogManager()
	);
}

void State_Start::Exit()
{
}