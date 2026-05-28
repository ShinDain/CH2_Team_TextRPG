#include "pch.h"
#include "State_Result.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "Manager/RecordManager.h"
#include "Map/MapManager.h"


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
	ConsoleRenderer::SetCursorPosition(100, 13);
	ConsoleUtil::WriteColored(GetResultTitle(ResultType), GetResultTitleColor(ResultType));

	
	//RecordManager 기록 보여주기
	RecordManager& Record = RecordManager::GetInstance();

	ConsoleRenderer::SetCursorPosition(98, 16);
	ConsoleUtil::WriteColored("[ 전적 통계 ]", ConsoleColor::Cyan);

	if (ResultType == EResultType::GameOver)
	{
		const MapNode* CurrentNode = Instance.GetMapManager().GetCurrentNode();
		int DeadFloor = (CurrentNode != nullptr) ? CurrentNode->Floor : 0;

		ConsoleRenderer::SetCursorPosition(88, 18);
		ConsoleUtil::WriteColored("최종 도달 : ", ConsoleColor::Red);
		GInput << DeadFloor << " 층에서 장렬히 전사";
	}
	else
	{
		ConsoleRenderer::SetCursorPosition(82, 18);
		ConsoleUtil::WriteColored("축하합니다! 던전의 모든 위협을 뚫고 살아남았습니다.", ConsoleColor::Green);
	}
	ConsoleRenderer::SetCursorPosition(91, 19);
	GInput << "- 일반몹 처치 : " << Record.GetMonsterKills() << " 마리";

	ConsoleRenderer::SetCursorPosition(91, 20);
	GInput << "- 엘리트 처치 : " << Record.GetEliteKills() << " 마리";

	ConsoleRenderer::SetCursorPosition(91, 21);
	GInput << "- 총 방문 노드 : " << Record.GetTotalNodeVisits() << " 개";

	ConsoleRenderer::SetCursorPosition(96, 22);
	GInput << "전투(M): " << Record.GetNodeVisitCount(ENodeType::Monster) << "회";

	ConsoleRenderer::SetCursorPosition(96, 23);
	GInput << "엘리트(E): " << Record.GetNodeVisitCount(ENodeType::Elite) << "회";

	ConsoleRenderer::SetCursorPosition(96, 24);
	GInput << "상점($): " << Record.GetNodeVisitCount(ENodeType::Shop) << "회";

	ConsoleRenderer::SetCursorPosition(95, 28);
	GInput << "1. 시작 메뉴로";
	ConsoleRenderer::SetCursorPosition(95, 30);
	GInput << "0. 종료";
	ConsoleRenderer::SetCursorPosition(90, 32);
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
		RecordManager::GetInstance().Initialize();
		StateManager::GetInstance().ChangeState(EState::Start);
	}
}

void State_Result::Exit()
{
}
