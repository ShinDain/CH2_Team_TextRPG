#include "pch.h"
#include "UI/BattleRenderer.h"
#include "Manager/InputManager.h"

#include "UI/ConsoleUtil.h"
#include "UI/AsciiArtLoader.h"

#include <windows.h>

BattleRenderer::BattleRenderer()
	: CurrentMonsterName("")
{
}

void BattleRenderer::SetMonsterName(const std::string& monsterName)
{
	CurrentMonsterName = monsterName;
}

void BattleRenderer::ClearMonsters()
{
	MonsterViews.clear();
}

void BattleRenderer::AddMonster(const std::string& monsterName, int drawX, int drawY)
{
	MonsterViews.push_back({ monsterName, drawX, drawY });
}

void BattleRenderer::DrawAllMonsterIdle()
{
	ConsoleUtil::HideCursor();
	ClearMonsterArea();

	for (const BattleMonsterView& MonsterView : MonsterViews)
	{
		DrawMonsterFrameAt(MonsterView.MonsterName, "idle", MonsterView.DrawX, MonsterView.DrawY);
	}
}

void BattleRenderer::DrawBattleScreen()
{
	ConsoleUtil::HideCursor();
	ClearBattleArea();
	DrawBattleTitle();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 5);
	GInput << "몬스터가 나타났다!";

	if (MonsterViews.empty())
	{
		DrawMonsterFrame(GetMonsterIdleFrame());
	}
	else
	{
		for (const BattleMonsterView& MonsterView : MonsterViews)
		{
			DrawMonsterFrameAt(MonsterView.MonsterName, "idle", MonsterView.DrawX, MonsterView.DrawY);
		}
	}
}

void BattleRenderer::DrawMonsterIdle()
{
	if (!MonsterViews.empty())
	{
		DrawAllMonsterIdle();
		return;
	}

	ClearMonsterArea();

	DrawMonsterFrame(GetMonsterIdleFrame());
}

void BattleRenderer::PlayMonsterAttackAnimation()
{
	if (!MonsterViews.empty())
	{
		PlayMonsterAttackAnimation(0);
		return;
	}

	ConsoleUtil::HideCursor();

	ClearMonsterArea();
	DrawMonsterFrame(GetMonsterAttackFrame());

	Sleep(120);

	ClearMonsterArea();
	DrawMonsterFrame(GetMonsterIdleFrame());
}

void BattleRenderer::PlayMonsterAttackAnimation(int monsterIndex)
{
	if (monsterIndex < 0 || monsterIndex >= static_cast<int>(MonsterViews.size()))
	{
		return;
	}

	ConsoleUtil::HideCursor();
	ClearMonsterArea();

	for (int i = 0; i < static_cast<int>(MonsterViews.size()); i++)
	{
		const BattleMonsterView& MonsterView = MonsterViews[i];
		const std::string State = (i == monsterIndex) ? "attack" : "idle";
		DrawMonsterFrameAt(MonsterView.MonsterName, State, MonsterView.DrawX, MonsterView.DrawY);
	}

	Sleep(120);
	DrawAllMonsterIdle();
}

void BattleRenderer::PlayMonsterHitAnimation()
{
	if (!MonsterViews.empty())
	{
		PlayMonsterHitAnimation(0);
		return;
	}

	ConsoleUtil::HideCursor();

	ClearMonsterArea();
	DrawMonsterFrame(GetMonsterHitFrame());

	Sleep(300);

	ClearMonsterArea();
	DrawMonsterFrame(GetMonsterIdleFrame());
}

void BattleRenderer::PlayMonsterHitAnimation(int monsterIndex)
{
	if (monsterIndex < 0 || monsterIndex >= static_cast<int>(MonsterViews.size()))
	{
		return;
	}

	ConsoleUtil::HideCursor();
	ClearMonsterArea();

	for (int i = 0; i < static_cast<int>(MonsterViews.size()); i++)
	{
		const BattleMonsterView& MonsterView = MonsterViews[i];
		const std::string State = (i == monsterIndex) ? "hit" : "idle";
		DrawMonsterFrameAt(MonsterView.MonsterName, State, MonsterView.DrawX, MonsterView.DrawY);
	}

	Sleep(300);
	DrawAllMonsterIdle();
}

void BattleRenderer::PlayMonsterDeathAnimation()
{
	ConsoleUtil::HideCursor();
	ClearMonsterArea();

	if (MonsterViews.empty())
	{
		DrawMonsterFrame(GetMonsterHitFrame());
	}
	else
	{
		for (int i = 0; i < static_cast<int>(MonsterViews.size()); i++)
		{
			const BattleMonsterView& MonsterView = MonsterViews[i];
			const std::string State = (i == 0) ? "hit" : "idle";
			DrawMonsterFrameAt(MonsterView.MonsterName, State, MonsterView.DrawX, MonsterView.DrawY);
		}
	}

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

void BattleRenderer::ClearMonsterArea()
{
	ConsoleUtil::ClearArea(
		MonsterAreaX,
		MonsterAreaY,
		MonsterAreaWidth,
		MonsterAreaHeight
	);
}

void BattleRenderer::DrawMonsterFrame(const std::vector<std::string>& frame)
{
	DrawFrameAt(
		MonsterDrawX,
		MonsterDrawY,
		frame
	);
}

void BattleRenderer::DrawMonsterFrameAt(
	const std::string& monsterName,
	const std::string& state,
	int drawX,
	int drawY
)
{
	DrawFrameAt(
		drawX,
		drawY,
		AsciiArtLoader::LoadFrame(monsterName, state)
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
		GInput << frame[i].substr(startIndex, maxLength);
	}

	ConsoleUtil::ResetTextColor();
}

void BattleRenderer::DrawBattleTitle()
{
	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 1);
	ConsoleUtil::SetTextColor(ConsoleColor::Red);
	GInput << "[ 전투 화면 ]";
	ConsoleUtil::ResetTextColor();

	ConsoleUtil::SetCursorPosition(BattleAreaX + 5, BattleAreaY + 3);
	ConsoleUtil::SetTextColor(ConsoleColor::Yellow);
	GInput << "몬스터: " << CurrentMonsterName;
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
