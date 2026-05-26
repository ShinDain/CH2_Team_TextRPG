#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_Stat_Attack :public Effect
{
public:
	Effect_Stat_Attack(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	int Value;
};

class Effect_Stat_Defense :public Effect
{
public:
	Effect_Stat_Defense(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	int Value;
};

class Effect_Stat_MaxHP :public Effect
{
public:
	Effect_Stat_MaxHP(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	int Value;
};

class Effect_Stat_MaxMP :public Effect
{
public:
	Effect_Stat_MaxMP(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	int Value;
};

class Effect_Stat_ActionSpeed :public Effect
{
public:
	Effect_Stat_ActionSpeed(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	int Value;
};

inline Effect* CreateStat_AttackInstance(int Value)
{
	return new Effect_Stat_Attack(Value);
}

inline bool bStat_AttackEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_STAT_ATTACK, CreateStat_AttackInstance);

inline Effect* CreateStat_DefenseInstance(int Value)
{
	return new Effect_Stat_Defense(Value);
}

inline bool bStat_DefenseEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_STAT_DEFENSE, CreateStat_DefenseInstance);

inline Effect* CreateStat_MaxHPInstance(int Value)
{
	return new Effect_Stat_MaxHP(Value);
}

inline bool bStat_MaxHPEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_STAT_MAXHP, CreateStat_MaxHPInstance);

inline Effect* CreateStat_MaxMPInstance(int Value)
{
	return new Effect_Stat_MaxMP(Value);
}

inline bool bStat_MaxMPEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_STAT_MAXMP, CreateStat_MaxMPInstance);

inline Effect* CreateStat_ActionSpeedInstance(int Value)
{
	return new Effect_Stat_ActionSpeed(Value);
}

inline bool bStat_ActionSpeedEffectRegister = EffectFactory::RegisterEffect(EFFECT_TAG_STAT_ACTIONSPEED, CreateStat_ActionSpeedInstance);
