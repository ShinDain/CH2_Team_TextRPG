#include "pch.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent(Object* InOwner) :
	Component(InOwner, "Skill")
{
}

SkillComponent::~SkillComponent()
{
}

bool SkillComponent::Initialize()
{
	return true;
}

void SkillComponent::AddSkill(uint16_t SkillId)
{
	LearnedSkills.insert(SkillId);
}

const std::set<uint16_t>& SkillComponent::GetLearnedSkills() const
{
	return LearnedSkills;
}

void SkillComponent::UpdateCooldowns()
{
	for (auto& pair : CurrentCooldowns)
	{
		if (pair.second > 0)
		{
			pair.second--;
		}
	}
}

bool SkillComponent::IsSkillReady(uint16_t SkillId) const
{
	auto it = CurrentCooldowns.find(SkillId);
	if (it != CurrentCooldowns.end())
	{
		return it->second <= 0;
	}
	return true; 
}

void SkillComponent::ApplyCooldown(uint16_t SkillId, uint8_t CooldownAmount)
{
	if (CooldownAmount > 0)
	{
		CurrentCooldowns[SkillId] = CooldownAmount;
	}
}