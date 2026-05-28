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

void BattleRenderer::AddMonster(const std::string& monsterName, int drawX, int drawY, int currentHP, int maxHP)
{
	const int SafeMaxHP = maxHP < 0 ? 0 : maxHP;
	const int SafeCurrentHP = SafeMaxHP > 0
		? (currentHP < 0 ? 0 : (currentHP > SafeMaxHP ? SafeMaxHP : currentHP))
		: (currentHP < 0 ? 0 : currentHP);

	MonsterViews.push_back({ monsterName, drawX, drawY, SafeCurrentHP, SafeMaxHP });
}

void BattleRenderer::DrawAllMonsterIdle()
{
	ConsoleUtil::HideCursor();
	ClearMonsterArea();

	for (const BattleMonsterView& MonsterView : MonsterViews)
	{
		DrawMonsterFrameAt(MonsterView, "idle");
	}
}

void BattleRenderer::SetMonsterHP(int monsterIndex, int currentHP)
{
	if (monsterIndex < 0 || monsterIndex >= static_cast<int>(MonsterViews.size()))
	{
		return;
	}

	BattleMonsterView& MonsterView = MonsterViews[monsterIndex];
	MonsterView.CurrentHP = MonsterView.MaxHP > 0
		? (currentHP < 0 ? 0 : (currentHP > MonsterView.MaxHP ? MonsterView.MaxHP : currentHP))
		: (currentHP < 0 ? 0 : currentHP);

	DrawAllMonsterIdle();
}

void BattleRenderer::DecreaseMonsterHP(int monsterIndex, int amount)
{
	if (monsterIndex < 0 || monsterIndex >= static_cast<int>(MonsterViews.size()) || amount <= 0)
	{
		return;
	}

	SetMonsterHP(monsterIndex, MonsterViews[monsterIndex].CurrentHP - amount);
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
			DrawMonsterFrameAt(MonsterView, "idle");
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
		DrawMonsterFrameAt(MonsterView, State);
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
		DrawMonsterFrameAt(MonsterView, State);
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
			DrawMonsterFrameAt(MonsterView, State);
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
	const BattleMonsterView& monsterView,
	const std::string& state,
	int offsetX,
	int offsetY
)
{
	const int DrawX = monsterView.DrawX + offsetX;
	const int DrawY = monsterView.DrawY + offsetY;

	DrawMonsterStatusAt(monsterView, DrawX, DrawY - 3);
	DrawFrameAt(
		DrawX,
		DrawY,
		AsciiArtLoader::LoadFrame(monsterView.MonsterName, state)
	);
}

void BattleRenderer::DrawMonsterStatusAt(const BattleMonsterView& monsterView, int x, int y)
{
	if (y < BattleAreaY + 1)
	{
		return;
	}

	ConsoleUtil::SetCursorPosition(x, y);
	ConsoleUtil::WriteColored(monsterView.MonsterName, ConsoleColor::White);

	ConsoleUtil::SetCursorPosition(x, y + 1);
	ConsoleUtil::WriteGauge(monsterView.CurrentHP, monsterView.MaxHP, 18, ConsoleColor::Red);
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
