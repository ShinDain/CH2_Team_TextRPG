#include "pch.h"
#include "State_Result.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "Manager/RecordManager.h"

namespace
{
std::string GetResultTitle(EResultType ResultType)
{
	return ResultType == EResultType::Clear ? "게임 클리어" : "게임 오버";
}

ConsoleColor GetResultTitleColor(EResultType ResultType)
{
	return ResultType == EResultType::Clear ? ConsoleColor::Yellow : ConsoleColor::Red;
}
}

State_Result::State_Result()
{
	Name = "Result";
}

void State_Result::Enter()
{
	GameInstance& Instance = GameInstance::GetInstance();

	if (Instance.GetResultType() == EResultType::Clear)
	{
		Instance.GetLogManager().AddLog("게임을 클리어했습니다.");
	}
	else
	{
		Instance.GetLogManager().AddLog("플레이어가 쓰러졌습니다.");
		Instance.GetLogManager().AddLog("게임 오버입니다.");
	}
}

void State_Result::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();
	const EResultType ResultType = Instance.GetResultType();

	ConsoleRenderer::ClearScreen();
	ConsoleUtil::HideCursor();

	ConsoleRenderer::DrawBox(55, 10, 100, 24);
	ConsoleRenderer::SetCursorPosition(94, 13);
	ConsoleUtil::WriteColored(GetResultTitle(ResultType), GetResultTitleColor(ResultType));

	
	//RecordManager 기록 보여주기
	RecordManager& Record = RecordManager::GetInstance();

	ConsoleRenderer::SetCursorPosition(94, 17);
	ConsoleUtil::WriteColored("[ 전적 통계 ]", ConsoleColor::Cyan);

	ConsoleRenderer::SetCursorPosition(82, 18);
	GInput << "- 일반몹 처치 : " << Record.GetMonsterKills() << " 마리";

	ConsoleRenderer::SetCursorPosition(82, 19);
	GInput << "- 엘리트 처치 : " << Record.GetEliteKills() << " 마리";

	ConsoleRenderer::SetCursorPosition(82, 20);
	GInput << "- 총 방문 노드 : " << Record.GetTotalNodeVisits() << " 개";

	// 종류별 노드 방문 횟수를 한 줄로 깔끔하게 배치
	ConsoleRenderer::SetCursorPosition(85, 21);
	GInput << "전투(M): " << Record.GetNodeVisitCount(ENodeType::Monster) << "회";

	ConsoleRenderer::SetCursorPosition(85, 22);
	GInput << "엘리트(E): " << Record.GetNodeVisitCount(ENodeType::Elite) << "회";

	ConsoleRenderer::SetCursorPosition(85, 23);
	GInput << "상점($): " << Record.GetNodeVisitCount(ENodeType::Shop) << "회";

	ConsoleRenderer::SetCursorPosition(78, 28);
	GInput << "1. 시작 메뉴로";
	ConsoleRenderer::SetCursorPosition(78, 30);
	GInput << "0. 종료";
	ConsoleRenderer::SetCursorPosition(78, 32);
	GInput << "입력 >> ";

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		return;
	}

	if (Input == 0)
	{
		Instance.Quit();
	}
	else if (Input == 1)
	{
		StateManager::GetInstance().ChangeState(EState::Start);
	}
}

void State_Result::Exit()
{
}
