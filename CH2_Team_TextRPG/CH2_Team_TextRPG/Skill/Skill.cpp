#include "pch.h"
#include "Skill.h"
#include "Effect/Effect.h"
#include "Character/Component/EffectComponent.h"
#include "Data/Table/SkillDataTable.h"


Skill::Skill(const FSkillData* InData) : Data(InData), CurrentCooldown(0)
{
}

Skill::~Skill()
{
}

void Skill::Active(Object* Instigator, std::vector<Object*> Targets)
{
	if (Instigator == nullptr || Targets.empty())
		return;

	for (Object* target : Targets)
	{
		for (Effect* effect : Effects)
		{
			if (effect == nullptr)
				continue;

			if (Data->Duration > 0)
			{
				auto effectComp = target->FindComponent<EffectComponent>("Effect");
				if (effectComp)
				{
					effectComp->AddActiveEffect(effect, Instigator, Data->Duration);
				}
			}
			
			int applyCount = Data->HitCount > 0 ? Data->HitCount : 1;
			for (int i = 0; i < applyCount; ++i)
			{
				// TODO : 각 Effect의 명중 처리
				bool bIsHit = true;

				if (bIsHit)
					effect->Apply(Instigator, { target });
			}
		}
	}
}

void Skill::AddEffect(Effect* InEffect)
{
	if (InEffect)
	{
		Effects.emplace_back(InEffect);
	}
}

void Skill::UpdateCooldown()
{
	if (CurrentCooldown > 0)
		CurrentCooldown--;
}

void Skill::ApplyCooldown()
{
	CurrentCooldown = Data->Cooldown;
}

bool Skill::IsReady() const
{
	return CurrentCooldown == 0;
}