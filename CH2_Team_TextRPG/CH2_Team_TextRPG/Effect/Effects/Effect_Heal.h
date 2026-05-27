#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"
#include "Character/Component/HealthComponent.h"

class Effect_Heal : public Effect
{
public:
	Effect_Heal(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

inline Effect* CreateHealEffectInstance(int Value)
{
	return new Effect_Heal(Value);
}

inline bool bHealEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_HEAL, CreateHealEffectInstance);