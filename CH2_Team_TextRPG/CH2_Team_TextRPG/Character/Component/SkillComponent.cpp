#include "pch.h"
#include "SkillComponent.h"
#include "Character/Component/ResourceComponent.h"
#include "Data/Character/Stat.h"
#include "Data/Table/SkillDataTable.h"
#include "Effect/Factory/EffectFactory.h"
#include "Skill/Skill.h"

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
	for (Skill* skill : LearnedSkills)
	{
		skill->UpdateCooldown();
	}
}

bool SkillComponent::IsSkillReady(uint16_t SkillId) const
{
	Skill* skill = FindSkillById(SkillId);
	if (skill)
	{
		return skill->IsReady();
	}
	return false;
}

void SkillComponent::ApplyCooldown(uint16_t SkillId)
{
	Skill* skill = FindSkillById(SkillId);
	if (skill)
	{
		skill->ApplyCooldown();
	}
}
void SkillComponent::ApplyCooldown(const Skill* InSkill)
{
	if (InSkill && InSkill->GetSkillData())
	{
		ApplyCooldown(InSkill->GetSkillData()->Idx);
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
			auto manaComponent = this->FindComponent<ResourceComponent>("Resource");
			if(manaComponent && manaComponent->GetCurrent(EResourceType::Mana) >= skillData->ManaCost)
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
			auto manaComponent = this->FindComponent<ResourceComponent>("Mana");
			if (manaComponent)
			{
				manaComponent->Decrease(EResourceType::Mana, skillData->ManaCost);
				return true;
			}
		}
	}
	return false;
}
bool SkillComponent::ConsumeCost(const Skill* InSkill)
{
	if (InSkill && InSkill->GetSkillData())
	{
		return ConsumeCost(InSkill->GetSkillData()->Idx);
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
