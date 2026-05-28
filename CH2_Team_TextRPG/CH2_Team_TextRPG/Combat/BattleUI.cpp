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
	if (!SkillComp || SkillComp->GetLearnedSkills().size() <= 1)
	{
		GInput << "사용 가능한 스킬이 없습니다.\n";
		return nullptr;
	}

	const auto& LearnedSkills = SkillComp->GetLearnedSkills();
	while (true)
	{
		GInput << "\n스킬을 선택하세요. (0: 취소)\n";
		int idx = 1;
		// 0번 인덱스(기본 공격)를 제외하고 1번부터 출력합니다.
		for (size_t i = 1; i < LearnedSkills.size(); ++i)
		{
			Skill* skill = LearnedSkills[i];
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
		if (GInput.IsFailed() || choice < 1 || choice >= LearnedSkills.size())
		{
			GInput << "유효하지 않은 입력입니다.\n";
			continue;
		}

		Skill* selectedSkill = LearnedSkills[choice];
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
