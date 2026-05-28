#include "pch.h"
#include "State_Start.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "UI/JobSelectUIFlow.h"
#include "UI/StartMenuScreen.h"

State_Start::State_Start()
{
	Name = "Start";
}

void State_Start::Enter()
{
	CurrentMode = EStartScreenMode::StartMenu;
	GameInstance::GetInstance().GetLogManager().AddLog("시작 메뉴에 진입했습니다.");
}

void State_Start::Process()
{
	switch (CurrentMode)
	{
	case EStartScreenMode::StartMenu:
		ProcessStartMenu();
		break;
	case EStartScreenMode::JobSelect:
		ProcessJobSelect();
		break;
	default:
		CurrentMode = EStartScreenMode::StartMenu;
		break;
	}
}

void State_Start::Exit()
{
}

void State_Start::ProcessStartMenu()
{
	GameInstance& Instance = GameInstance::GetInstance();

	StartMenuScreen::Draw();

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		Instance.GetLogManager().AddLog("메뉴 번호를 다시 선택해주세요.");
		return;
	}

	switch (Input)
	{
	case 1:
		CurrentMode = EStartScreenMode::JobSelect;
		break;
	case 2:
		Instance.GetLogManager().AddLog("불러오기 로직은 아직 연결되지 않았습니다.");
		break;
	case 0:
		Instance.Quit();
		break;
	default:
		Instance.GetLogManager().AddLog("메뉴 번호를 다시 선택해주세요.");
		break;
	}
}

void State_Start::ProcessJobSelect()
{
	const EJobSelectUIResult Result = JobSelectUIFlow::Process();
	if (Result == EJobSelectUIResult::BackToStart)
	{
		CurrentMode = EStartScreenMode::StartMenu;
	}
}
