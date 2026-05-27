#include "pch.h"
#include "Effect_Stat.h"
#include "Character/Component/StatComponent.h"
#include "Data/Character/Stat.h"

void AdjustOwnerStat(Object* Instigator, EStatType Type, int Delta)
{
	if (!Instigator) return;
	if (auto Stat = Instigator->FindComponent<StatComponent>("Stat"))
	{
		Stat->AddStat(Type, Delta);
	}
}

// --- Attack ---
Effect_Stat_Attack::Effect_Stat_Attack(int InValue)
	:Effect(EFFECT_TAG_STAT_ATTACK, InValue)
{
}

void Effect_Stat_Attack::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::Attack, +Value);
}

void Effect_Stat_Attack::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::Attack, -Value);
}

// --- Defense ---
Effect_Stat_Defense::Effect_Stat_Defense(int InValue)
	:Effect(EFFECT_TAG_STAT_DEFENSE, InValue)
{
}

void Effect_Stat_Defense::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::Defense, +Value);
}

void Effect_Stat_Defense::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::Defense, -Value);
}

// --- MaxHP ---
Effect_Stat_MaxHP::Effect_Stat_MaxHP(int InValue)
	:Effect(EFFECT_TAG_STAT_MAXHP, InValue)
{
}

void Effect_Stat_MaxHP::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::MaxHP, +Value);
}

void Effect_Stat_MaxHP::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::MaxHP, -Value);
}

// --- MaxMP ---
Effect_Stat_MaxMP::Effect_Stat_MaxMP(int InValue)
	:Effect(EFFECT_TAG_STAT_MAXMP, InValue)
{
}

void Effect_Stat_MaxMP::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::MaxMP, +Value);
}

void Effect_Stat_MaxMP::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::MaxMP, -Value);
}

// --- ActionSpeed ---
Effect_Stat_ActionSpeed::Effect_Stat_ActionSpeed(int InValue)
	:Effect(EFFECT_TAG_STAT_ACTIONSPEED, InValue)
{
}

void Effect_Stat_ActionSpeed::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::ActionSpeed, +Value);
}

void Effect_Stat_ActionSpeed::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	AdjustOwnerStat(Instigator, EStatType::ActionSpeed, -Value);
}
