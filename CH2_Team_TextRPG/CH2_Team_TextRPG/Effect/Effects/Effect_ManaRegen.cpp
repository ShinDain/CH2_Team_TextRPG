#include "pch.h"
#include "Effect_ManaRegen.h"
#include "Core/Object.h"
#include "Character/Interface/Resource.h"
#include "Data/Character/Stat.h"

Effect_ManaRegen::Effect_ManaRegen(int InValue)
	:Effect(Game::EffectTag::Resource::RecoveryMana, InValue)
{
}

void Effect_ManaRegen::Apply(Object* Instigator, std::vector<Object*> Targets)
{
	if (Instigator == nullptr
		|| Targets.empty())
		return;

	for (Object* target : Targets)
	{
		IResource* resource = dynamic_cast<IResource*>(target);
		resource->Recovery(EResourceType::Mana, Value);
	}

	GLog.AddLog("[Effect_ManaRegen] Applied");
	return;
}

void Effect_ManaRegen::Remove(Object* Instigator, std::vector<Object*> Targets)
{
}
