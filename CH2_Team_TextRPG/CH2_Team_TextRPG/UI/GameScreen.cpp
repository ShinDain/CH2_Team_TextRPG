#include "pch.h"
#include "GameScreen.h"
#include "ConsoleRenderer.h"

void GameScreen::DrawMainScreen(const MapManager& Map, const LogManager& Log)
{
	ConsoleRenderer::ClearScreen();

	DrawCharacterPanel();
	DrawInventoryPanel();
	DrawMapPanel(Map);
	DrawLogPanel(Log);
	DrawInputPanel();
}

void GameScreen::DrawCharacterPanel()
{
	ConsoleRenderer::DrawBox(0, 0, 30, 11);
	ConsoleRenderer::DrawString(2, 1, "캐릭터 정보");
	ConsoleRenderer::DrawString(2, 3, "이름 : 전사");
	ConsoleRenderer::DrawString(2, 4, "직업 : 기사");
	ConsoleRenderer::DrawString(2, 5, "체력 : 72 / 76");
	ConsoleRenderer::DrawString(2, 6, "골드 : 155");
	ConsoleRenderer::DrawString(2, 7, "층   : 1");
}

void GameScreen::DrawInventoryPanel()
{
	ConsoleRenderer::DrawBox(0, 11, 30, 12);
	ConsoleRenderer::DrawString(2, 12, "인벤토리");
	ConsoleRenderer::DrawString(2, 14, "포션 x2");
	ConsoleRenderer::DrawString(2, 15, "철검");
	ConsoleRenderer::DrawString(2, 16, "가죽 갑옷");
}

void GameScreen::DrawMapPanel(const MapManager& Map)
{
	ConsoleRenderer::DrawBox(30, 0, 88, 23);
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

	ConsoleRenderer::DrawLines(42, 4, MapLines);

	const MapNode* CurrentNode = Map.GetCurrentNode();

	if (CurrentNode != nullptr)
	{
		ConsoleRenderer::DrawString(34, 15, "현재 위치");
		ConsoleRenderer::DrawString(34, 16, "번호 : " + std::to_string(CurrentNode->Id));
		ConsoleRenderer::DrawString(34, 17, "종류 : " + MapManager::NodeTypeToString(CurrentNode->Type));
		ConsoleRenderer::DrawString(34, 18, "층   : " + std::to_string(CurrentNode->Floor));
	}

	std::vector<int> MovableNodeIds = Map.GetMovableNodeIds();

	ConsoleRenderer::DrawString(65, 15, "이동 가능 노드");

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

		ConsoleRenderer::DrawString(65, 16 + i, Text);
	}
}

void GameScreen::DrawLogPanel(const LogManager& Log)
{
	ConsoleRenderer::DrawBox(0, 23, 118, 7);
	ConsoleRenderer::DrawString(2, 24, "로그");

	ConsoleRenderer::DrawString(2, 26, "> 게임을 시작했습니다.");
	ConsoleRenderer::DrawString(2, 27, "> 던전 지도가 생성되었습니다.");
	ConsoleRenderer::DrawString(2, 28, "> 이동할 노드를 선택하세요.");
}

void GameScreen::DrawInputPanel()
{
	ConsoleRenderer::DrawString(2, 31, "이동할 노드 번호 입력 >> ");
}