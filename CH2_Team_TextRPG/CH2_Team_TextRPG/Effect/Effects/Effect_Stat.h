#pragma once
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"

class Effect_Stat_Attack :public Effect
{
public:
	Effect_Stat_Attack(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

};

class Effect_Stat_Defense :public Effect
{
public:
	Effect_Stat_Defense(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

};

class Effect_Stat_Health :public Effect
{
public:
	Effect_Stat_Health(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

};

class Effect_Stat_Mana :public Effect
{
public:
	Effect_Stat_Mana(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

};

class Effect_Stat_ActionSpeed :public Effect
{
public:
	Effect_Stat_ActionSpeed(int InValue);

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) override;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) override;

};

inline Effect* CreateStat_AttackInstance(int Value)
{
	return new Effect_Stat_Attack(Value);
}

inline bool bStat_AttackEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Stat::Attack, CreateStat_AttackInstance);

inline Effect* CreateStat_DefenseInstance(int Value)
{
	return new Effect_Stat_Defense(Value);
}

inline bool bStat_DefenseEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Stat::Defense, CreateStat_DefenseInstance);

inline Effect* CreateStat_HealthInstance(int Value)
{
	return new Effect_Stat_Health(Value);
}

inline bool bStat_HealthEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Stat::Health, CreateStat_HealthInstance);

inline Effect* CreateStat_ManaInstance(int Value)
{
	return new Effect_Stat_Mana(Value);
}

inline bool bStat_ManaEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Stat::Mana, CreateStat_ManaInstance);

inline Effect* CreateStat_ActionSpeedInstance(int Value)
{
	return new Effect_Stat_ActionSpeed(Value);
}

inline bool bStat_ActionSpeedEffectRegister = EffectFactory::RegisterEffect(Game::EffectTag::Stat::ActionSpeed, CreateStat_ActionSpeedInstance);
