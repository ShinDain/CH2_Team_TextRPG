#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_ManaRegen : public Effect
{
public:
	Effect_ManaRegen(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;
};

inline Effect* CreateManaRegenEffectInstance(int Value)
{
	return new Effect_ManaRegen(Value);
}

inline bool bManaRegenEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Resource::RecoveryMana, CreateManaRegenEffectInstance);
