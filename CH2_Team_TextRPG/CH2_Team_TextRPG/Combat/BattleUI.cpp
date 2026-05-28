#include "pch.h"
#include "BattleUI.h"
#include "Manager/InputManager.h"
#include "Character/Component/SkillComponent.h"
#include "Data/Table/SkillDataTable.h"

EActionType BattleUI::ShowActionMenu()
{
	int InputChoice = -1;
	while (true)
	{
		GInput << "\n어떤 행동을 하시겠습니까?\n1. 공격\n2. 스킬\n3. 아이템\n";
		GInput >> InputChoice;

		if (GInput.IsFailed() || InputChoice < 1 || InputChoice > 3)
		{
			GInput << "유효하지 않은 입력입니다. 다시 입력해주세요.\n";
			continue;
		}
		return static_cast<EActionType>(InputChoice - 1);
	}
}

Skill* BattleUI::ShowSkillMenu(std::shared_ptr<SkillComponent> SkillComp)
{
	if (!SkillComp || SkillComp->GetLearnedSkills().empty())
	{
		GInput << "사용 가능한 스킬이 없습니다.\n";
		return nullptr;
	}

	const auto& LearnedSkills = SkillComp->GetLearnedSkills();
	while (true)
	{
		GInput << "\n스킬을 선택하세요. (0: 취소)\n";
		int idx = 1;
		for (Skill* skill : LearnedSkills)
		{
			uint16_t skillId = skill->GetSkillData()->Idx;
			GInput << idx++ << ". " << skill->GetSkillData()->Name 
				   << " [MP:" << skill->GetSkillData()->ManaCost << "] "
				   << " [쿨타임:" << (int)skill->GetCurrentCooldown() << "] ";
			
			if (!SkillComp->IsSkillReady(skillId) || !SkillComp->CheckCost(skillId))
				GInput << "- [X]\n";
			else
				GInput << "- [O]\n";
		}

		int choice = -1;
		GInput >> choice;

		if (choice == 0) return nullptr;

		if (GInput.IsFailed() || choice < 1 || choice > LearnedSkills.size())
		{
			GInput << "유효하지 않은 입력입니다.\n";
			continue;
		}

		Skill* selectedSkill = LearnedSkills[choice - 1];
		uint16_t selectedSkillId = selectedSkill->GetSkillData()->Idx;

		if (!SkillComp->IsSkillReady(selectedSkillId))
		{
			GInput << "현재 쿨타임 중이라 사용할 수 없습니다.\n";
			continue;
		}
		if (!SkillComp->CheckCost(selectedSkillId))
		{
			GInput << "마나가 부족하여 사용할 수 없습니다.\n";
			continue;
		}

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
		GInput << "\n대상을 선택하세요. [ 남은 선택 횟수: " << (TargetCount - TargetList.size()) << " ] (0: 취소)\n";
		for (size_t i = 0; i < SelectableMonsters.size(); ++i)
		{
			GInput << i + 1 << ". " << SelectableMonsters[i]->GetName() << "\n";
		}

		int choice = -1;
		GInput >> choice;

		if (choice == 0) return std::vector<Object*>();

		if (GInput.IsFailed() || choice < 1 || choice > SelectableMonsters.size())
		{
			GInput << "유효하지 않은 입력입니다. 다시 선택해주세요.\n";
			continue;
		}

		TargetList.push_back(SelectableMonsters[choice - 1]);
		SelectableMonsters.erase(SelectableMonsters.begin() + (choice - 1));
	}

	return TargetList;
}
