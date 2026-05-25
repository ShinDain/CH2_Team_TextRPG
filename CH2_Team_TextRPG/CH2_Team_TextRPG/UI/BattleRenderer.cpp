#include "pch.h"
#include "UI/BattleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "UI/AnimationFrameData.h"

#include <iostream>
#include <windows.h>

void BattleRenderer::DrawBattleScreen()
{
	ClearBattleArea();
	DrawBattleTitle();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 3);
	std::cout << "몬스터가 나타났다!";

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);
}

void BattleRenderer::DrawMonsterIdle()
{
	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);
	Sleep(250);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 11,
		AnimationFrameData::GetSlimeIdle2()
	);
	Sleep(250);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);
}

void BattleRenderer::PlayPlayerAttackAnimation()
{
	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);

	DrawFrameAt(
		BattleAreaX + 55,
		BattleAreaY + 12,
		AnimationFrameData::GetSlash1()
	);
	Sleep(120);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 72,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);

	DrawFrameAt(
		BattleAreaX + 60,
		BattleAreaY + 12,
		AnimationFrameData::GetSlash2()
	);
	Sleep(120);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);
}

void BattleRenderer::PlayMonsterHitAnimation()
{
	for (int i = 0; i < 3; i++)
	{
		ClearBattleArea();
		DrawBattleTitle();

		DrawFrameAt(
			BattleAreaX + 67,
			BattleAreaY + 10,
			AnimationFrameData::GetSlimeIdle1()
		);

		DrawFrameAt(
			BattleAreaX + 78,
			BattleAreaY + 8,
			AnimationFrameData::GetHitEffect()
		);
		Sleep(80);

		ClearBattleArea();
		DrawBattleTitle();

		DrawFrameAt(
			BattleAreaX + 73,
			BattleAreaY + 10,
			AnimationFrameData::GetSlimeIdle1()
		);

		DrawFrameAt(
			BattleAreaX + 78,
			BattleAreaY + 8,
			AnimationFrameData::GetHitEffect()
		);
		Sleep(80);
	}

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);
}

void BattleRenderer::PlayMonsterDeathAnimation()
{
	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeIdle1()
	);
	Sleep(200);

	ClearBattleArea();
	DrawBattleTitle();

	DrawFrameAt(
		BattleAreaX + 70,
		BattleAreaY + 10,
		AnimationFrameData::GetSlimeDead()
	);
	Sleep(700);

	ClearBattleArea();
	DrawBattleTitle();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 70, BattleAreaY + 14);
	std::cout << "몬스터를 처치했다!";
}

void BattleRenderer::PlayNormalBattleAnimation()
{
	DrawBattleScreen();
	Sleep(500);

	DrawMonsterIdle();
	Sleep(300);

	PlayPlayerAttackAnimation();
	Sleep(200);

	PlayMonsterHitAnimation();
	Sleep(300);

	PlayPlayerAttackAnimation();
	Sleep(200);

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
	for (int i = 0; i < static_cast<int>(frame.size()); i++)
	{
		ConsoleUtil::SetCursorPosition(x, y + i);
		std::cout << frame[i];
	}
}

void BattleRenderer::DrawBattleTitle()
{
	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 1);
	std::cout << "[ 전투 화면 ]";
}