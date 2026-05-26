#include "pch.h"
#include "Effect_Stat.h"

Effect_Stat_Attack::Effect_Stat_Attack(int InValue)
	:Effect(EFFECT_TAG_STAT_ATTACK), Value(InValue)
{
}

void Effect_Stat_Attack::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	GLog.AddLog("[Effect_Stat_Attack] Effect Applied.");
}

Effect_Stat_Defense::Effect_Stat_Defense(int InValue)
	:Effect(EFFECT_TAG_STAT_DEFENSE), Value(InValue)
{
}

void Effect_Stat_Defense::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
}

Effect_Stat_MaxHP::Effect_Stat_MaxHP(int InValue)
	:Effect(EFFECT_TAG_STAT_MAXHP), Value(InValue)
{
}

void Effect_Stat_MaxHP::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
}

Effect_Stat_MaxMP::Effect_Stat_MaxMP(int InValue)
	:Effect(EFFECT_TAG_STAT_MAXMP), Value(InValue)
{
}

void Effect_Stat_MaxMP::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
}

Effect_Stat_ActionSpeed::Effect_Stat_ActionSpeed(int InValue)
	:Effect(EFFECT_TAG_STAT_ACTIONSPEED), Value(InValue)
{
}

void Effect_Stat_ActionSpeed::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
}
