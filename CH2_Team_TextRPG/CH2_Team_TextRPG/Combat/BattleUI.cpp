#include "pch.h"
#include "BattleUI.h"
#include "Manager/InputManager.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Monster/Monster.h"
#include "Character/Player/Player.h"
#include "Character/Interface/Resource.h"
#include "Data/Character/Stat.h"
#include "UI/BattleRenderer.h"
#include "UI/GameScreen.h"
#include "UI/ConsoleUtil.h"
#include <windows.h>
#include <map>

namespace
{
	// BattleUI 내부에서만 사용할 렌더러 인스턴스
	BattleRenderer Renderer;
	std::map<Object*, int> RenderedMonsterIndices;

	std::vector<std::pair<int, int>> MakeMonsterPositions(int MonsterCount)
	{
		std::vector<std::pair<int, int>> Positions;
		const int ClampedCount = MonsterCount < 1 ? 1 : MonsterCount;
		const int Gap = 50;
		const int CenterX = 105;
		const int StartX = CenterX - ((ClampedCount - 1) * Gap / 2);

		for (int i = 0; i < ClampedCount; i++)
		{
			Positions.push_back({ StartX + (i * Gap), 8 });
		}
		return Positions;
	}

	void ClearInputLine()
	{
		ConsoleUtil::ClearArea(2, 48, 205, 1);
	}

	void ShowPromptMessage(const std::string& Message)
	{
		ClearInputLine();
		ConsoleUtil::SetCursorPosition(2, 48);
		ConsoleUtil::WriteColored(Message, ConsoleColor::White);
	}

	void ShowErrorMessage(const std::string& Message)
	{
		ClearInputLine();
		ConsoleUtil::SetCursorPosition(2, 48);
		ConsoleUtil::WriteColored(Message, ConsoleColor::Red);
		Sleep(1000);
	}
}

void BattleUI::DrawBattleView(const std::vector<Monster*>& AliveMonsters)
{
	Renderer.ClearMonsters();
	RenderedMonsterIndices.clear();
	std::vector<std::pair<int, int>> Positions = MakeMonsterPositions(static_cast<int>(AliveMonsters.size()));

	for (size_t i = 0; i < AliveMonsters.size(); i++)
	{
		IResource* resource = dynamic_cast<IResource*>(AliveMonsters[i]);
		int CurHP = resource ? resource->GetCurrentResource(EResourceType::Health) : 100;
		int MaxHP = resource ? resource->GetMaxResource(EResourceType::Health) : 100;
		Renderer.AddMonster(AliveMonsters[i]->GetName(), Positions[i].first, Positions[i].second, CurHP, MaxHP);
		RenderedMonsterIndices[AliveMonsters[i]] = i;
	}

	GameScreen::DrawCharacterPanel(GameInstance::GetInstance().GetMainPlayer());
	Renderer.DrawBattleScreen();
	GameScreen::DrawLogPanel(GameInstance::GetInstance().GetLogManager());
}

void BattleUI::PlayHitAnimation(const std::vector<Object*>& Targets)
{
	for (Object* target : Targets)
	{
		if (RenderedMonsterIndices.find(target) != RenderedMonsterIndices.end())
		{
			Renderer.PlayMonsterHitAnimation(RenderedMonsterIndices[target]);
		}
	}
}

void BattleUI::PlayAttackAnimation(Object* Attacker)
{
	if (RenderedMonsterIndices.find(Attacker) != RenderedMonsterIndices.end())
	{
		Renderer.PlayMonsterAttackAnimation(RenderedMonsterIndices[Attacker]);
	}
}

EActionType BattleUI::ShowActionMenu()
{
	int InputChoice = -1;
	while (true)
	{
		std::vector<FCommandOption> Options = {
			{ "1. 공격", true },
			{ "2. 스킬", true },
			{ "3. 아이템", true }
		};
		GameScreen::DrawBattleCommandPanel("행동 선택", Options);

		ShowPromptMessage("어떤 행동을 하시겠습니까? >> ");

		GInput >> InputChoice;

		if (GInput.IsFailed() || InputChoice < 1 || InputChoice > 3)
		{
			ShowErrorMessage("유효하지 않은 입력입니다. 다시 입력해주세요.");
			continue;
		}
		ClearInputLine();
		return static_cast<EActionType>(InputChoice - 1);
	}
}

Skill* BattleUI::ShowSkillMenu(std::shared_ptr<SkillComponent> SkillComp)
{
	if (!SkillComp || SkillComp->GetLearnedSkills().size() <= 1)
	{
		ShowErrorMessage("사용 가능한 스킬이 없습니다.");
		return nullptr;
	}

	const auto& LearnedSkills = SkillComp->GetLearnedSkills();
	while (true)
	{
		std::vector<FCommandOption> Options;
		for (size_t i = 1; i < LearnedSkills.size(); ++i)
		{
			Skill* skill = LearnedSkills[i];
			uint16_t skillId = skill->GetSkillData()->Idx;
			bool bIsReady = SkillComp->IsSkillReady(skillId);
			bool bCanCost = SkillComp->CheckCost(skillId);
			
			std::string Text = std::to_string(i) + ". " + skill->GetSkillData()->Name;
			Text += " [MP " + std::to_string(skill->GetSkillData()->ManaCost) + "]";
			if (!bIsReady) Text += " (쿨타임:" + std::to_string(skill->GetCurrentCooldown()) + ")";
			if (!bCanCost) Text += " (마나부족)";
			
			Options.push_back({ Text, bIsReady && bCanCost });
		}
		GameScreen::DrawBattleCommandPanel("스킬 선택", Options);

		ShowPromptMessage("스킬을 선택하세요. (0: 취소) >> ");

		int choice = -1;
		GInput >> choice;

		if (choice == 0)
		{
			ClearInputLine();
			return nullptr;
		}

		if (GInput.IsFailed() || choice < 1 || choice >= LearnedSkills.size())
		{
			ShowErrorMessage("유효하지 않은 입력입니다.");
			continue;
		}

		Skill* selectedSkill = LearnedSkills[choice];
		uint16_t selectedSkillId = selectedSkill->GetSkillData()->Idx;

		if (!SkillComp->IsSkillReady(selectedSkillId))
		{
			ShowErrorMessage("현재 쿨타임 중이라 사용할 수 없습니다.");
			continue;
		}
		if (!SkillComp->CheckCost(selectedSkillId))
		{
			ShowErrorMessage("마나가 부족하여 사용할 수 없습니다.");
			continue;
		}

		ClearInputLine();
		return selectedSkill;
	}
}

std::vector<Object*> BattleUI::ShowTargetMenu(const std::vector<Monster*>& AliveMonsters, int TargetCount)
{
	std::vector<Object*> TargetList;
	if (TargetCount >= AliveMonsters.size())
	{
		for (Monster* m : AliveMonsters) TargetList.push_back(m);
		return TargetList;
	}

	std::vector<Monster*> SelectableMonsters = AliveMonsters;
	while (TargetList.size() < TargetCount && !SelectableMonsters.empty())
	{
		std::vector<FCommandOption> Options;
		for (size_t i = 0; i < SelectableMonsters.size(); ++i)
		{
			Options.push_back({ std::to_string(i + 1) + ". " + SelectableMonsters[i]->GetName(), true });
		}
		GameScreen::DrawBattleCommandPanel("대상 선택", Options);

		std::string prompt = "대상을 선택하세요. [ 남은 선택 횟수: " + std::to_string(TargetCount - TargetList.size()) + " ] (0: 취소) >> ";
		ShowPromptMessage(prompt);

		int choice = -1;
		GInput >> choice;

		if (choice == 0)
		{
			ClearInputLine();
			return std::vector<Object*>();
		}

		if (GInput.IsFailed() || choice < 1 || choice > SelectableMonsters.size())
		{
			ShowErrorMessage("유효하지 않은 입력입니다. 다시 선택해주세요.");
			continue;
		}

		TargetList.push_back(SelectableMonsters[choice - 1]);
		SelectableMonsters.erase(SelectableMonsters.begin() + (choice - 1));
	}

	ClearInputLine();
	return TargetList;
}
