#include "pch.h"
#include "State_Entry.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

State_Entry::State_Entry()
{
}

void State_Entry::Enter()
{
	ConsoleRenderer::SetupLargeConsole();
	ConsoleUtil::HideCursor();
	GLog.AddLog("초기화가 완료되었습니다.");
}

void State_Entry::Process()
{
	StateManager::GetInstance().ChangeState(EState::Start);
}

void State_Entry::Exit()
{
}
