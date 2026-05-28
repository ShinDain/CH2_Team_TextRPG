#include "pch.h"
#include "Effect_Debuff_Stun.h"

Effect_Debuff_Stun::Effect_Debuff_Stun(int InValue)
	:Effect(Game::EffectTag::State::Stun, InValue)
{
}

void Effect_Debuff_Stun::Apply(Object* Instigator, std::vector<class Object*> Targets)
{

}

void Effect_Debuff_Stun::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
}
