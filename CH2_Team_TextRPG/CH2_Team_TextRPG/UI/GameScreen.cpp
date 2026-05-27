#include "pch.h"
#include "GameScreen.h"
#include "ConsoleRenderer.h"
#include "ConsoleUtil.h"

namespace
{
struct MapNodeView
{
	int NodeId;
	int X;
	int Y;
};

char GetMapNodeIcon(ENodeType Type)
{
	switch (Type)
	{
	case ENodeType::Start:
		return 'S';
	case ENodeType::Monster:
		return 'M';
	case ENodeType::Event:
		return '?';
	case ENodeType::Shop:
		return '$';
	case ENodeType::Treasure:
		return '?';
	case ENodeType::Rest:
		return 'R';
	case ENodeType::Elite:
		return 'E';
	case ENodeType::Boss:
		return 'B';
	default:
		return '?';
	}
}

void DrawMapPath(int FromX, int FromY, int ToX, int ToY, ConsoleColor Color, bool bHighlighted)
{
	if (FromX == ToX && FromY == ToY)
	{
		return;
	}

	const int DeltaX = ToX - FromX;
	const int DeltaY = ToY - FromY;
	const int AbsDeltaX = DeltaX < 0 ? -DeltaX : DeltaX;
	const int AbsDeltaY = DeltaY < 0 ? -DeltaY : DeltaY;
	const int Steps = AbsDeltaX > AbsDeltaY ? AbsDeltaX : AbsDeltaY;

	if (Steps <= 1)
	{
		return;
	}

	std::vector<float> Points = bHighlighted
		? std::vector<float>{ 0.25f, 0.5f, 0.75f }
		: std::vector<float>{ 0.33f, 0.66f };

	for (float T : Points)
	{
		const int X = static_cast<int>(FromX + static_cast<float>(DeltaX) * T);
		const int Y = static_cast<int>(FromY + static_cast<float>(DeltaY) * T);

		if (X <= 32 || X >= 208 || Y <= 1 || Y >= 33)
		{
			continue;
		}

		ConsoleRenderer::SetCursorPosition(X, Y);
		ConsoleUtil::WriteColored(bHighlighted ? "*" : ".", Color);
	}
}
}

void GameScreen::DrawMainScreen(const MapManager& Map, const LogManager& Log)
{
	ConsoleRenderer::ClearScreen();

	DrawCharacterPanel();
	DrawInventoryPanel();
	DrawMapPanel(Map);
	DrawNavigationPanel(Map);
	DrawLogPanel(Log);
	DrawInputPanel();
}

void GameScreen::DrawCharacterPanel()
{
	ConsoleRenderer::DrawBox(0, 0, 30, 11);
	ConsoleRenderer::SetCursorPosition(2, 1);
	ConsoleUtil::WriteColored("캐릭터 정보", ConsoleColor::Cyan);
	ConsoleRenderer::SetCursorPosition(2, 3);
	ConsoleUtil::WriteColored("이름 : 전사", ConsoleColor::Gray);
	ConsoleRenderer::SetCursorPosition(2, 4);
	ConsoleUtil::WriteColored("직업 : 기사", ConsoleColor::Gray);
	ConsoleRenderer::SetCursorPosition(2, 5);
	ConsoleUtil::WriteColored("체력 : 72 / 76", ConsoleColor::Red);
	ConsoleRenderer::SetCursorPosition(2, 6);
	ConsoleUtil::WriteColored("골드 : 155", ConsoleColor::Yellow);
	ConsoleRenderer::SetCursorPosition(2, 7);
	ConsoleUtil::WriteColored("층   : 1", ConsoleColor::Gray);
}

void GameScreen::DrawInventoryPanel()
{
	ConsoleRenderer::DrawBox(0, 11, 30, 23);
	ConsoleRenderer::SetCursorPosition(2, 12);
	ConsoleUtil::WriteColored("인벤토리", ConsoleColor::Yellow);
	ConsoleRenderer::SetCursorPosition(2, 14);
	ConsoleUtil::WriteColored("포션 x2", ConsoleColor::White);
	ConsoleRenderer::SetCursorPosition(2, 15);
	ConsoleUtil::WriteColored("철검", ConsoleColor::White);
	ConsoleRenderer::SetCursorPosition(2, 16);
	ConsoleUtil::WriteColored("가죽 갑옷", ConsoleColor::White);
}

void GameScreen::DrawMapPanel(const MapManager& Map)
{
	ConsoleRenderer::DrawBox(30, 0, 180, 34);
	ConsoleRenderer::DrawString(32, 1, "던전 지도");

	std::vector<MapNodeView> NodeViews =
	{
		{ 31, 112, 2 },

		{ 28, 84, 4 },
		{ 29, 112, 4 },
		{ 30, 140, 4 },

		{ 25, 76, 7 },
		{ 26, 106, 7 },
		{ 27, 146, 7 },

		{ 22, 88, 10 },
		{ 23, 118, 10 },
		{ 24, 140, 10 },

		{ 19, 76, 13 },
		{ 20, 112, 13 },
		{ 21, 148, 13 },

		{ 16, 92, 16 },
		{ 17, 122, 16 },
		{ 18, 144, 16 },

		{ 13, 76, 19 },
		{ 14, 108, 19 },
		{ 15, 140, 19 },

		{ 10, 88, 22 },
		{ 11, 118, 22 },
		{ 12, 148, 22 },

		{ 7, 76, 25 },
		{ 8, 106, 25 },
		{ 9, 136, 25 },

		{ 4, 88, 28 },
		{ 5, 118, 28 },
		{ 6, 146, 28 },

		{ 1, 84, 30 },
		{ 2, 112, 30 },
		{ 3, 140, 30 },

		{ 0, 112, 32 }
	};

	const MapNode* CurrentNode = Map.GetCurrentNode();
	std::vector<int> MovableNodeIds = Map.GetMovableNodeIds();

	auto FindView = [&NodeViews](int NodeId) -> const MapNodeView*
	{
		for (const MapNodeView& View : NodeViews)
		{
			if (View.NodeId == NodeId)
			{
				return &View;
			}
		}

		return nullptr;
	};

	auto IsMovableNode = [&MovableNodeIds](int NodeId)
	{
		return std::find(MovableNodeIds.begin(), MovableNodeIds.end(), NodeId) != MovableNodeIds.end();
	};

	for (const MapNodeView& FromView : NodeViews)
	{
		const MapNode* FromNode = Map.GetNodeById(FromView.NodeId);

		if (FromNode == nullptr)
		{
			continue;
		}

		for (int ToNodeId : FromNode->ConnectedNodeIds)
		{
			const MapNodeView* ToView = FindView(ToNodeId);

			if (ToView == nullptr)
			{
				continue;
			}

			const bool bIsCurrentOutgoing =
				CurrentNode != nullptr &&
				CurrentNode->Id == FromNode->Id &&
				IsMovableNode(ToNodeId);

			DrawMapPath(
				FromView.X,
				FromView.Y,
				ToView->X,
				ToView->Y,
				bIsCurrentOutgoing ? ConsoleColor::Green : ConsoleColor::DarkGray,
				bIsCurrentOutgoing
			);
		}
	}

	for (const MapNodeView& View : NodeViews)
	{
		const MapNode* Node = Map.GetNodeById(View.NodeId);

		if (Node == nullptr)
		{
			continue;
		}

		const std::string Label(1, GetMapNodeIcon(Node->Type));

		ConsoleRenderer::SetCursorPosition(View.X, View.Y);

		if (CurrentNode != nullptr && CurrentNode->Id == View.NodeId)
		{
			ConsoleUtil::WriteColored(Label, ConsoleColor::Yellow);
		}
		else if (IsMovableNode(View.NodeId))
		{
			ConsoleUtil::WriteColored(Label, ConsoleColor::Green);
		}
		else if (Node->bIsVisited)
		{
			ConsoleUtil::WriteColored(Label, ConsoleColor::DarkYellow);
		}
		else if (Node->Type == ENodeType::Boss)
		{
			ConsoleUtil::WriteColored(Label, ConsoleColor::Magenta);
		}
		else
		{
			ConsoleUtil::WriteColored(Label, ConsoleColor::Gray);
		}
	}

	ConsoleRenderer::SetCursorPosition(34, 2);
	ConsoleUtil::WriteColored("S 시작  M 전투  ? 이벤트  $ 상점  R 휴식  E 엘리트  B 보스", ConsoleColor::DarkGray);
}

void GameScreen::DrawNavigationPanel(const MapManager& Map)
{
	ConsoleRenderer::DrawBox(0, 34, 210, 6);
	ConsoleRenderer::SetCursorPosition(2, 35);
	ConsoleUtil::WriteColored("탐험 정보", ConsoleColor::Cyan);

	const MapNode* CurrentNode = Map.GetCurrentNode();

	if (CurrentNode != nullptr)
	{
		ConsoleRenderer::SetCursorPosition(4, 36);
		ConsoleUtil::WriteColored("현재 위치", ConsoleColor::Gray);
		ConsoleRenderer::SetCursorPosition(4, 37);
		ConsoleUtil::WriteColored("번호 : " + std::to_string(CurrentNode->Id), ConsoleColor::Gray);
		ConsoleRenderer::SetCursorPosition(20, 37);
		ConsoleUtil::WriteColored("종류 : " + MapManager::NodeTypeToString(CurrentNode->Type), ConsoleColor::Gray);
		ConsoleRenderer::SetCursorPosition(40, 37);
		ConsoleUtil::WriteColored("층 : " + std::to_string(CurrentNode->Floor), ConsoleColor::Gray);
	}

	std::vector<int> MovableNodeIds = Map.GetMovableNodeIds();

	ConsoleRenderer::SetCursorPosition(95, 35);
	ConsoleUtil::WriteColored("이동 가능 노드", ConsoleColor::Green);

	for (int i = 0; i < static_cast<int>(MovableNodeIds.size()); i++)
	{
		const MapNode* Node = Map.GetNodeById(MovableNodeIds[i]);

		if (Node == nullptr)
		{
			continue;
		}

		std::string Text = std::to_string(i + 1) + ". " +
			MapManager::NodeTypeToString(Node->Type) +
			" [노드 번호: " + std::to_string(Node->Id) + "]";

		ConsoleRenderer::SetCursorPosition(95, 36 + i);
		ConsoleUtil::WriteColored(Text, ConsoleColor::White);
	}
}

void GameScreen::DrawLogPanel(const LogManager& Log)
{
	ConsoleRenderer::DrawBox(0, 40, 210, 10);
	ConsoleRenderer::SetCursorPosition(2, 41);
	ConsoleUtil::WriteColored("로그", ConsoleColor::Cyan);

	std::vector<std::string> RecentLogs = Log.GetRecentLogs(5);

	if (RecentLogs.empty())
	{
		ConsoleRenderer::SetCursorPosition(2, 43);
		ConsoleUtil::WriteColored("> 로그가 없습니다.", ConsoleColor::Gray);
		return;
	}

	for (int i = 0; i < static_cast<int>(RecentLogs.size()); i++)
	{
		ConsoleRenderer::SetCursorPosition(2, 43 + i);
		ConsoleUtil::WriteColored("> " + RecentLogs[i], ConsoleColor::Gray);
	}
}

void GameScreen::DrawInputPanel()
{
	ConsoleRenderer::SetCursorPosition(2, 48);
	ConsoleUtil::WriteColored("이동할 노드 번호 입력 >> ", ConsoleColor::White);
}
