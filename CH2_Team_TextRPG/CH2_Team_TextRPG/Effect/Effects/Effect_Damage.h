#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_Damage : public Effect
{
public:
	Effect_Damage(int InValue);
	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

class Effect_Fixed_Damage : public Effect
{
public:
	Effect_Fixed_Damage(int InValue);
	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

inline Effect* CreateDamageEffectInstance(int Value)
{
	return new Effect_Damage(Value);
}

inline Effect* CreateFixedDamageEffectInstance(int Value)
{
	return new Effect_Fixed_Damage(Value);
}

inline bool bDamageEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Damage::Damage, CreateDamageEffectInstance);
inline bool bFixedDamageEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Damage::FixedDamage, CreateFixedDamageEffectInstance);