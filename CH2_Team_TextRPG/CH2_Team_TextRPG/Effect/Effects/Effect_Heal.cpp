#include "pch.h"
#include "Effect_Heal.h"
#include "Core/Object.h"
#include "Character/Interface/Resource.h"
#include "Data/Character/Stat.h"

Effect_Heal::Effect_Heal(int InValue)
	:Effect(Game::EffectTag::Resource::RecoveryHeal, InValue)
{
}

void Effect_Heal::Apply(Object* Instigator, std::vector<Object*> Targets)
{
	if (Instigator == nullptr
		|| Targets.empty())
		return;

	for (Object* target : Targets)
	{
		IResource* resource = dynamic_cast<IResource*>(target);
		resource->Recovery(EResourceType::Health, Value);
	}

	GLog.AddLog("[Effect_Heal] Applied");
	return;
}

void Effect_Heal::Remove(class Object* Instigator, std::vector<Object*> Targets)
{
}
