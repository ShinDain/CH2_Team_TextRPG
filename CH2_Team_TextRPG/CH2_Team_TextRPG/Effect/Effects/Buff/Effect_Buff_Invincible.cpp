#include "pch.h"
#include "Effect_Buff_Invincible.h"

Effect_Buff_Invincible::Effect_Buff_Invincible(int InValue)
	:Effect(Game::EffectTag::State::Invincible, InValue)
{
}

void Effect_Buff_Invincible::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	// 피해를 이번 턴동안 무시합니다.
}

void Effect_Buff_Invincible::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
}
