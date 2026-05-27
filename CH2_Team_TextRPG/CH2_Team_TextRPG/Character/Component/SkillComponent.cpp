#include "pch.h"
#include "SkillComponent.h"
#include "Character/Component/HealthComponent.h"	
#include "Data/Table/SkillDataTable.h"
#include "Effect/Factory/EffectFactory.h"

SkillComponent::SkillComponent(Object* InOwner) :
	Component(InOwner, "Skill")
{
}

SkillComponent::~SkillComponent()
{
	for (Skill* skill : LearnedSkills)
	{
		delete skill;
	}
	LearnedSkills.clear();
}

bool SkillComponent::Initialize()
{
	return true;
}

void SkillComponent::AddSkill(uint16_t SkillId)
{
	// 중복 스킬 습득 방지
	for (Skill* skill : LearnedSkills)
	{
		if (skill->GetSkillData()->Idx == SkillId)
			return;
	}

	const FSkillData* Data = SkillDataTable::GetInstance().FindSkillDataByIndex(SkillId);
	if (Data != nullptr)
	{
		Skill* newSkill = new Skill(Data);
		for (const EffectData& effectData : Data->Effects)
		{
			newSkill->AddEffect(EffectFactory::CreateEffect(effectData));
		}
		LearnedSkills.push_back(newSkill);
	}
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

bool SkillComponent::CheckCost(uint16_t SkillId)
{
	Skill* skill = FindSkillById(SkillId);
	if (skill)
	{
		const FSkillData* skillData = skill->GetSkillData();
		if (skillData)
		{
			auto manaComponent = this->FindComponent<HealthComponent>("Mana");
			if (manaComponent && manaComponent->GetCurrent() >= skillData->ManaCost)
			{
				return true;
			}
		}
	}
	return false;
}

bool SkillComponent::ConsumeCost(uint16_t SkillId)
{
	Skill* skill = FindSkillById(SkillId);
	if (skill)
	{
		const FSkillData* skillData = skill->GetSkillData();
		if (skillData)
		{
			auto manaComponent = this->FindComponent<HealthComponent>("Mana");
			if (manaComponent)
			{
				manaComponent->Decrease(skillData->ManaCost);
				return true;
			}
		}
	}
	return false;
}
bool SkillComponent::ConsumeCost(const Skill* InSkill)
{
	if (InSkill)
	{
		const FSkillData* skillData = InSkill->GetSkillData();
		if (skillData)
		{
			auto manaComponent = this->FindComponent<HealthComponent>("Mana");
			if (manaComponent)
			{
				manaComponent->Decrease(skillData->ManaCost);
				return true;
			}
		}
	}
	return false;
}

Skill* SkillComponent::FindSkillById(uint16_t SkillId) const
{
	for (Skill* skill : LearnedSkills)
	{
		if (skill->GetSkillData()->Idx == SkillId)
		{
			return skill;
		}
	}
	return nullptr;
}
