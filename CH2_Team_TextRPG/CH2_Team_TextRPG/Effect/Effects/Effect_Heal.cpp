#include "pch.h"
#include "Effect_Heal.h"

Effect_Heal::Effect_Heal(int InValue)
	:Effect(Game::EffectTag::Resource::RecoveryHeal, InValue)
{
}

void Effect_Heal::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	if (Instigator == nullptr
		|| Targets.empty())
		return;

	GInput << "[Effect_Heal] Applied\n";
	return;
}

void Effect_Heal::Remove(class Object* Instigator, std::vector<class Object*> Targets)
{
}
