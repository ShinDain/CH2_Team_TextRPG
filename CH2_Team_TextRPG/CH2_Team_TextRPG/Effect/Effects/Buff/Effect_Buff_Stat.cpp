#include "pch.h"
#include "Effect_Buff_Stat.h"
#include "Core/Object.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"

void ApplyBuffStat(Object* StatObject, EStatType Type, int Delta)
{
	if (auto UnitStat = dynamic_cast<IUnitStat*>(StatObject))
		UnitStat->ApplyStat(Type, Delta);
}

Effect_Buff_Attack::Effect_Buff_Attack(int InValue)
	:Effect(Game::EffectTag::Buff::Attack, InValue)
{
	bApply = false;
}

void Effect_Buff_Attack::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	if (bApply == false)
	{
		ApplyBuffStat(Instigator, EStatType::Attack, +Value);
		bApply = true;
	}
}

void Effect_Buff_Attack::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	if (bApply)
	{
		ApplyBuffStat(Instigator, EStatType::Attack, -Value);
		bApply = false;
	}
}

Effect_Buff_Defense::Effect_Buff_Defense(int InValue)
	:Effect(Game::EffectTag::Buff::Defense, InValue)
{
	bApply = false;
}

void Effect_Buff_Defense::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	if (bApply == false)
	{
		ApplyBuffStat(Instigator, EStatType::Defense, +Value);
		bApply = true;
	}
}

void Effect_Buff_Defense::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	if (bApply)
	{
		ApplyBuffStat(Instigator, EStatType::Defense, -Value);
		bApply = false;
	}
}

Effect_Buff_ActionSpeed::Effect_Buff_ActionSpeed(int InValue)
	:Effect(Game::EffectTag::Buff::ActionSpeed, InValue)
{
	bApply = false;
}

void Effect_Buff_ActionSpeed::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	if (bApply == false)
	{
		ApplyBuffStat(Instigator, EStatType::ActionSpeed, +Value);
		bApply = true;
	}
}

void Effect_Buff_ActionSpeed::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	if (bApply)
	{
		ApplyBuffStat(Instigator, EStatType::ActionSpeed, -Value);
		bApply = false;
	}
}
