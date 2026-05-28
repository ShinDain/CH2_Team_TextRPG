#include "pch.h"
#include "GameProgress.h"

#include "Character/Player/Player.h"
#include "Data/Character/Stat.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"

#include "UI/ConsoleRenderer.h"
#include "UI/GameScreen.h"

bool GameProgress::HandleNodeSelection(MapManager& Map, LogManager& Log)
{
	std::vector<int> MovableNodeIds = Map.GetMovableNodeIds();

	if (MovableNodeIds.empty())
	{
		Log.AddLog("이동 가능한 노드가 없습니다.");
		return false;
	}

	int Input = 0;
	ConsoleRenderer::SetCursorPosition(28, 48);
	std::cin >> Input;

	if (Input < 1 || Input > static_cast<int>(MovableNodeIds.size()))
	{
		Log.AddLog("잘못된 노드를 선택했습니다.");
		return false;
	}

	int SelectedNodeId = MovableNodeIds[Input - 1];

	const MapNode* SelectedNode = Map.GetNodeById(SelectedNodeId);

	if (SelectedNode == nullptr)
	{
		Log.AddLog("선택한 노드가 존재하지 않습니다.");
		return false;
	}

	bool IsMoveSuccess = Map.MoveToNode(SelectedNodeId);

	if (IsMoveSuccess)
	{
		std::string NodeName = MapManager::NodeTypeToString(SelectedNode->Type);
		Log.AddLog(NodeName + " 노드로 이동했습니다.");
	}
	else
	{
		Log.AddLog("선택한 노드로 이동할 수 없습니다.");
	}

	return IsMoveSuccess;
}

void GameProgress::HandleCurrentNodeEvent(const MapManager& Map, LogManager& Log)
{
	const MapNode* CurrentNode = Map.GetCurrentNode();

	if (CurrentNode == nullptr)
	{
		Log.AddLog("현재 노드 정보를 찾을 수 없습니다.");
		return;
	}

	switch (CurrentNode->Type)
	{
	case ENodeType::Start:
		Log.AddLog("시작 지점에 도착했습니다.");
		break;

	case ENodeType::Monster:
		Log.AddLog("몬스터가 나타났습니다. 전투를 시작합니다.");
		break;

	case ENodeType::Elite:
		Log.AddLog("강력한 엘리트 몬스터가 나타났습니다.");
		break;

	case ENodeType::Event:
		Log.AddLog("수상한 이벤트가 발생했습니다.");
		break;

	case ENodeType::Shop:
		Log.AddLog("상점에 도착했습니다.");
		break;

	case ENodeType::Treasure:
		Log.AddLog("이벤트 지점에 도착했습니다.");
		break;

	case ENodeType::Rest:
	{
		Player* MainPlayer = GameInstance::GetInstance().GetMainPlayer();
		Log.AddLog("휴식 지점에 도착했습니다.");

		if (MainPlayer != nullptr)
		{
			const int MaxHP = MainPlayer->GetMaxResource(EResourceType::Health);
			const int HealAmount = std::max(1, static_cast<int>(MaxHP * 0.4f));
			MainPlayer->Recovery(EResourceType::Health, HealAmount);
			Log.AddLog("최대 체력의 40%를 회복했습니다.");
			GameScreen::DrawCharacterPanel(MainPlayer);
		}
		break;
	}

	case ENodeType::Boss:
		Log.AddLog("보스가 나타났습니다.");
		break;

	default:
		Log.AddLog("알 수 없는 노드입니다.");
		break;
	}
}

void GameProgress::EndGame(LogManager& Log)
{
	ConsoleRenderer::ClearScreen();

	GInput << "==============================\n";
	GInput << "          게임 클리어          \n";
	GInput << "==============================\n";

	Log.AddLog("게임을 클리어했습니다.");
	Log.PrintRecentLogs(10);

	GInput << "\n엔터를 누르면 종료됩니다...";

	std::cin.ignore();
	std::cin.get();
}
