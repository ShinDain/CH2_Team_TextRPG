#include "pch.h"
#include "Skill.h"
#include "Effect/Effect.h"


Skill::Skill(const FSkillData* InData) : Data(InData)
{
}

Skill::~Skill()
{
}

void Skill::Active(Object* Instigator, std::vector<Object*> Targets)
{
	if (Instigator == nullptr)
		return;
	for (Effect* effect : Effects)
	{
		if (effect == nullptr)
			continue;
		effect->Apply(Instigator, Targets);
	}
}

void Skill::AddEffect(Effect* InEffect)
{
	if (InEffect)
	{
		Effects.emplace_back(InEffect);
	}
}