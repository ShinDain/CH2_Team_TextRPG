#include "pch.h"
#include "GameScreen.h"
#include "ConsoleRenderer.h"
#include "ConsoleUtil.h"

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

	std::vector<std::string> MapLines =
	{
		"                         [Boss:6]",
		"                         /      \\",
		"                   [Rest:4]   [Elite:5]",
		"                      |          |",
		"                   [Shop:2]  [Monster:3]",
		"                        \\      /",
		"                       [Event:1]",
		"                           |",
		"                       [Start:0]"
	};

	ConsoleRenderer::DrawLines(98, 12, MapLines);
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

	ConsoleRenderer::SetCursorPosition(95, 36);
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

		ConsoleRenderer::SetCursorPosition(95, 37 + i);
		ConsoleUtil::WriteColored(Text, ConsoleColor::White);
	}
}

void GameScreen::DrawLogPanel(const LogManager& Log)
{
	ConsoleRenderer::DrawBox(0, 40, 210, 10);
	ConsoleRenderer::SetCursorPosition(2, 41);
	ConsoleUtil::WriteColored("로그", ConsoleColor::Cyan);

	ConsoleRenderer::SetCursorPosition(2, 43);
	ConsoleUtil::WriteColored("> 게임을 시작했습니다.", ConsoleColor::Gray);
	ConsoleRenderer::SetCursorPosition(2, 44);
	ConsoleUtil::WriteColored("> 던전 지도가 생성되었습니다.", ConsoleColor::Gray);
	ConsoleRenderer::SetCursorPosition(2, 45);
	ConsoleUtil::WriteColored("> 이동할 노드를 선택하세요.", ConsoleColor::Gray);
}

void GameScreen::DrawInputPanel()
{
	ConsoleRenderer::SetCursorPosition(2, 48);
	ConsoleUtil::WriteColored("이동할 노드 번호 입력 >> ", ConsoleColor::White);
}
