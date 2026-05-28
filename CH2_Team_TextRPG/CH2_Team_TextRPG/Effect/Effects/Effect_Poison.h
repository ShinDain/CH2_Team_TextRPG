#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_Poison : public Effect
{
public:
	Effect_Poison(int InValue);

	virtual void Apply(Object* Instigator, std::vector<Object*> Targets) override;
	virtual void Remove(Object* Instigator, std::vector<Object*> Targets) override;
};

inline Effect* CreateDebuff_PoisonEffectInstance(int Value)
{
	return new Effect_Poison(Value);
}

inline bool bDebuff_PoisonEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Debuff::Poison, CreateDebuff_PoisonEffectInstance);
