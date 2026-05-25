#include "pch.h"
#include "UI/BattleRenderer.h"

#include "UI/ConsoleUtil.h"
#include "UI/AsciiArtLoader.h"

#include <iostream>
#include <windows.h>

BattleRenderer::BattleRenderer()
	: CurrentMonsterName("goblin")
{
}

void BattleRenderer::SetMonsterName(const std::string& monsterName)
{
	CurrentMonsterName = monsterName;
}

void BattleRenderer::DrawBattleScreen()
{
	ClearBattleArea();
	DrawBattleTitle();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 5);
	std::cout << "몬스터가 나타났다!";

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterIdleFrame()
	);
}

void BattleRenderer::DrawMonsterIdle()
{
	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterIdleFrame()
	);
}

void BattleRenderer::PlayMonsterAttackAnimation()
{
	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterIdleFrame()
	);

	Sleep(120);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterAttackFrame()
	);

	Sleep(120);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterIdleFrame()
	);
}

void BattleRenderer::PlayMonsterHitAnimation()
{
	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterHitFrame()
	);

	Sleep(300);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		GetMonsterIdleFrame()
	);
}

void BattleRenderer::PlayMonsterDeathAnimation()
{
	ClearBattleArea();
	DrawBattleTitle();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 70, BattleAreaY + 14);
	std::cout << "몬스터를 처치했다!";

	Sleep(700);
}

void BattleRenderer::PlayNormalBattleAnimation()
{
	DrawBattleScreen();
	Sleep(500);

	PlayMonsterAttackAnimation();
	Sleep(200);

	PlayMonsterHitAnimation();
	Sleep(300);

	PlayMonsterAttackAnimation();
	Sleep(200);

	PlayMonsterHitAnimation();
	Sleep(300);

	PlayMonsterDeathAnimation();
	Sleep(700);
}

void BattleRenderer::ClearBattleArea()
{
	ConsoleUtil::ClearArea(
		BattleAreaX + 1,
		BattleAreaY + 1,
		BattleAreaWidth - 2,
		BattleAreaHeight - 2
	);
}

void BattleRenderer::DrawFrameAt(int x, int y, const std::vector<std::string>& frame)
{
	const int left = BattleAreaX + 1;
	const int right = BattleAreaX + BattleAreaWidth - 2;
	const int top = BattleAreaY + 1;
	const int bottom = BattleAreaY + BattleAreaHeight - 2;

	ConsoleUtil::SetTextColor(ConsoleColor::Green);

	for (int i = 0; i < static_cast<int>(frame.size()); i++)
	{
		const int targetY = y + i;

		if (targetY < top)
		{
			continue;
		}

		if (targetY > bottom)
		{
			break;
		}

		int targetX = x;
		std::size_t startIndex = 0;

		if (targetX < left)
		{
			startIndex = static_cast<std::size_t>(left - targetX);
			targetX = left;
		}

		if (targetX > right || startIndex >= frame[i].size())
		{
			continue;
		}

		const std::size_t maxLength = static_cast<std::size_t>(right - targetX + 1);

		ConsoleUtil::SetCursorPosition(targetX, targetY);
		std::cout << frame[i].substr(startIndex, maxLength);
	}

	ConsoleUtil::ResetTextColor();
}

void BattleRenderer::DrawBattleTitle()
{
	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 1);
	ConsoleUtil::SetTextColor(ConsoleColor::Red);
	std::cout << "[ 전투 화면 ]";
	ConsoleUtil::ResetTextColor();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 3);
	ConsoleUtil::SetTextColor(ConsoleColor::Yellow);
	std::cout << "몬스터: " << CurrentMonsterName;
	ConsoleUtil::ResetTextColor();
}

std::vector<std::string> BattleRenderer::GetMonsterIdleFrame() const
{
	return AsciiArtLoader::LoadFrame(CurrentMonsterName, "idle");
}

std::vector<std::string> BattleRenderer::GetMonsterHitFrame() const
{
	return AsciiArtLoader::LoadFrame(CurrentMonsterName, "hit");
}

std::vector<std::string> BattleRenderer::GetMonsterAttackFrame() const
{
	return AsciiArtLoader::LoadFrame(CurrentMonsterName, "attack");
}
