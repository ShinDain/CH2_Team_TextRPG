#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_Debuff_Stun : public Effect
{
public:
	Effect_Debuff_Stun(int InValue);
		
	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

inline Effect* CreateDebuff_StunEffectInstance(int Value)
{
	return new Effect_Debuff_Stun(Value);
}

inline bool bDebuff_StunEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::State::Stun, CreateDebuff_StunEffectInstance);