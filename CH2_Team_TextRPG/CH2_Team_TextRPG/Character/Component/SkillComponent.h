#pragma once
#include "Core/Component.h"
#include <set>

class SkillComponent : public Component
{
public:
	SkillComponent() = delete;
	SkillComponent(Object* InOwner);
	virtual ~SkillComponent();

	virtual bool Initialize() override;

	// 캐릭터에게 새로운 스킬을 가르칩니다.
	void AddSkill(uint16_t SkillId);

	// 보유한 스킬IDX 목록을 반환합니다.
	const std::set<uint16_t>& GetLearnedSkills() const;

	// 매 턴 시작 시 쿨타임을 1씩 감소시킵니다.
	void UpdateCooldowns();
	// 스킬 사용 가능 여부 (쿨타임이 0 이하인지) 확인합니다.
	bool IsSkillReady(uint16_t SkillId) const;
	// 스킬 사용 시 쿨타임을 적용합니다.
	void ApplyCooldown(uint16_t SkillId, uint8_t CooldownAmount);

private:
	// 사용가능한 스킬IDX 목록
	std::set<uint16_t> LearnedSkills; 
	// 스킬IDX별 남은 쿨타임
	std::map<uint16_t, uint8_t> CurrentCooldowns;
};