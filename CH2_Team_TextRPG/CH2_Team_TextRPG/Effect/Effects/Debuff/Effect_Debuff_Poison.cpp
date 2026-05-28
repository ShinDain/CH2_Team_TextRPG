#include "pch.h"
#include "Effect_Debuff_Poison.h"
#include "Character/Component/EffectComponent.h"
#include "Character/Component/ResourceComponent.h"
#include "Character/Interface/Damageable.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"

Effect_Debuff_Poison::Effect_Debuff_Poison(int InValue) : Effect(Game::EffectTag::Debuff::Poison, InValue)
{
}

void Effect_Debuff_Poison::Apply(Object* Instigator, std::vector<Object*> Targets)
{
	for (Object* Target : Targets)
	{
		auto TargetHP = dynamic_cast<IDamageable*>(Target);
		if (TargetHP)
		{
			TargetHP->TakeDamage(Value);
			GLog.AddLog("[독] " + Target->GetName() + "이(가) 독으로 인해 " + std::to_string(Value) + "의 피해를 입었습니다!");
		}
	}
}

void Effect_Debuff_Poison::Remove(Object* Instigator, std::vector<Object*> Targets)
{
	for (Object* Target : Targets)
	{
		GLog.AddLog(Target->GetName() + "의 독 지속시간이 만료되어 해제되었습니다.");
	}
}
