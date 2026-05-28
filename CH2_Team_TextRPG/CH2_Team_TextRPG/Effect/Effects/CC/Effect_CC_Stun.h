#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_CC_Stun : public Effect
{
public:
	Effect_CC_Stun(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

inline Effect* CreateCC_StunEffectInstance(int Value)
{
	return new Effect_CC_Stun(Value);
}

inline bool bCC_StunEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::State::Stun, CreateCC_StunEffectInstance);
