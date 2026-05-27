#include "pch.h"
#include "Effect_CC_Stun.h"

Effect_CC_Stun::Effect_CC_Stun(int InValue)
	:Effect(Game::EffectTag::CC::Stun, InValue)
{
}

void Effect_CC_Stun::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	// 턴을 스킵한다.
}

void Effect_CC_Stun::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
}
