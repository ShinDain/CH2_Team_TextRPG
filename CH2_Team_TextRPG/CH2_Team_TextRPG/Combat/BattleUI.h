#pragma once
#include "Core/Object.h"
#include "Skill/Skill.h"
#include "Character/Monster/Monster.h"

enum class EActionType
{
	ATTACK,
	SKILL,
	ITEM,
	CANCEL
};

class BattleUI
{
public:
	static void DrawBattleView(const std::vector<Monster*>& AliveMonsters);

	// 애니메이션 재생
	static void PlayHitAnimation(const std::vector<Object*>& Targets);
	static void PlayAttackAnimation(Object* Attacker);

	// 행동 메뉴 출력 및 선택 반환
	static EActionType ShowActionMenu();
	// 스킬 메뉴 출력 및 선택 반환 
	static Skill* ShowSkillMenu(std::shared_ptr<class SkillComponent> SkillComp);
	// 타겟 메뉴 출력 및 선택 반환
	static std::vector<Object*> ShowTargetMenu(const std::vector<Monster*>& AliveMonsters, int TargetCount);
};
