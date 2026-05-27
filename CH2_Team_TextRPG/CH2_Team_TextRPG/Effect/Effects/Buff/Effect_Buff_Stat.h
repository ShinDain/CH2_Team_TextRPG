#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

#include "Data/Character/Stat.h"

class Effect_Buff_Attack :public Effect
{
public:
	Effect_Buff_Attack(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	bool bApply;
};

class Effect_Buff_Defense :public Effect
{
public:
	Effect_Buff_Defense(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	bool bApply;
};

class Effect_Buff_ActionSpeed :public Effect
{
public:
	Effect_Buff_ActionSpeed(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	bool bApply;
};

inline Effect* CreateBuff_AttackEffectInstance(int Value)
{
	return new Effect_Buff_Attack(Value);
}
inline Effect* CreateBuff_DefenseEffectInstance(int Value)
{
	return new Effect_Buff_Defense(Value);
}
inline Effect* CreateBuff_ActionSpeedEffectInstance(int Value)
{
	return new Effect_Buff_ActionSpeed(Value);
}

inline bool bBuff_AttackEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Buff::Attack, CreateBuff_AttackEffectInstance);
inline bool bBuff_AttackEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Buff::Defense, CreateBuff_DefenseEffectInstance);
inline bool bBuff_AttackEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Buff::ActionSpeed, CreateBuff_ActionSpeedEffectInstance);

