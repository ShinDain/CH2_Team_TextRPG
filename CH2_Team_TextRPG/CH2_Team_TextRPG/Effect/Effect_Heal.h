#pragma once
#include "Effect.h"
#include "Factory/EffectFactory.h"
#include "Character/Component/HealthComponent.h"
#include <functional>

class Effect_Heal : public IEffect
{
public:
	Effect_Heal(int InValue);

	virtual void Apply(class Object* Target)
	{
		HealthComponent* healthComp = Target->FindComponent<HealthComponent>("Health");

		int a = 100;

		return;
	}
private:
	int Value;
};

inline IEffect* CreateHealEffectInstance(int Value)
{
	return new Effect_Heal(Value);
}

inline bool bHealEffectRegister = EffectFactory::RegisterEffect("Heal", CreateHealEffectInstance);