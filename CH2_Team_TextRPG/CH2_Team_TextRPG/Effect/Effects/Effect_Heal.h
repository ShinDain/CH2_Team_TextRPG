#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"
#include "Character/Component/HealthComponent.h"

class Effect_Heal : public Effect
{
public:
	Effect_Heal(int InValue);

	virtual void Apply(class Object* Target)
	{
		HealthComponent* healthComp = Target->FindComponent<HealthComponent>("Health");

		GInput << "[Effect_Heal] Applied";

		return;
	}
private:
	int Value;
};

inline Effect* CreateHealEffectInstance(int Value)
{
	return new Effect_Heal(Value);
}

inline bool bHealEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_HEAL, CreateHealEffectInstance);