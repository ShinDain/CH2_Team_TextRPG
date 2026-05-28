#include "pch.h"
#include "State_Start.h"

#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "Start/Condition/LoadGameCondition.h"
#include "Start/Condition/NewGameCondition.h"
#include "UI/StartMenuScreen.h"

State_Start::State_Start()
{
	Name = "Start";
}

void State_Start::Enter()
{
	GLog.AddLog("시작 메뉴에 진입했습니다.");
	
	AddTransition<NewGameCondition>(EState::Map);
	AddTransition<LoadGameCondition>(EState::Map);
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	StartMenuScreen::Draw();

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		GLog.AddLog("메뉴 번호를 다시 선택해주세요.");
		return;
	}

	switch (Input)
	{
		case 1:
		{
			// StateManager::GetInstance().ChangeState(EState::CharacterCreate);
			break;
		}


		case 2: GLog.AddLog("저장 데이터 로드는 아직 구현되지 않았습니다.");
			break;
		case 0:
			Instance.Quit();
			break;
		default: GLog.AddLog("메뉴 번호를 다시 선택해주세요.");
			break;
	}
}

void State_Start::Exit()
{
}
