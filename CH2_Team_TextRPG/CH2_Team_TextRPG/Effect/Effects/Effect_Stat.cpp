#include "pch.h"
#include "Effect_Stat.h"
#include "Core/Object.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"

void ApplyStat(Object* StatObject, EStatType Type, int Delta)
{
	if (auto UnitStat = dynamic_cast<IUnitStat*>(StatObject))
		UnitStat->ApplyStat(Type, Delta);
}

// --- Attack ---
Effect_Stat_Attack::Effect_Stat_Attack(int InValue)
	:Effect(Game::EffectTag::Stat::Attack, InValue)
{
}

void Effect_Stat_Attack::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Attack, -Value);
}

void Effect_Stat_Attack::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Attack, -Value);
}

// --- Defense ---
Effect_Stat_Defense::Effect_Stat_Defense(int InValue)
	:Effect(Game::EffectTag::Stat::Defence, InValue)
{
}

void Effect_Stat_Defense::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Defense, +Value);
}

void Effect_Stat_Defense::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Defense, -Value);
}

// --- Health ---
Effect_Stat_Health::Effect_Stat_Health(int InValue)
	:Effect(Game::EffectTag::Stat::Health, InValue)
{
}

void Effect_Stat_Health::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Health, +Value);
}

void Effect_Stat_Health::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Health, -Value);
}

// --- Mana ---
Effect_Stat_Mana::Effect_Stat_Mana(int InValue)
	:Effect(Game::EffectTag::Stat::Mana, InValue)
{
}

void Effect_Stat_Mana::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Mana, +Value);
}

void Effect_Stat_Mana::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::Mana, -Value);
}

// --- ActionSpeed ---
Effect_Stat_ActionSpeed::Effect_Stat_ActionSpeed(int InValue)
	:Effect(Game::EffectTag::Stat::ActionSpeed, InValue)
{
}

void Effect_Stat_ActionSpeed::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::ActionSpeed, +Value);
}

void Effect_Stat_ActionSpeed::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	ApplyStat(Instigator, EStatType::ActionSpeed, -Value);
}
