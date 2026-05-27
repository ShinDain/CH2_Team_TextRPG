#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_Buff_Invincible : public Effect
{
public:
	Effect_Buff_Invincible(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

inline Effect* CreateBuff_InvincibleEffectInstance(int Value)
{
	return new Effect_Buff_Invincible(Value);
}

inline bool bBuff_InvincibleEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Buff::Invincible, CreateBuff_InvincibleEffectInstance);
