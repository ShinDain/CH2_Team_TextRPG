#include "pch.h"
#include "Core/Object.h"
#include "Effect_Debuff_Burn.h"
#include "Effect/EffectTag.h"
#include "Character/Interface/Damageable.h"

Effect_Debuff_Burn::Effect_Debuff_Burn(int InValue)
	: Effect(Game::EffectTag::Debuff::Burn, InValue)
{
}

void Effect_Debuff_Burn::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		if (auto TargetHP = dynamic_cast<IDamageable*>(Target))
		{
			TargetHP->TakeDamage(Value);
			GLog.AddLog("[화상] " + Target->GetName() + "이(가) 화상으로 인해 " + std::to_string(Value) + "의 피해를 입었습니다!");
		}
	}
}

void Effect_Debuff_Burn::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		GLog.AddLog(Target->GetName() + "의 화상 지속시간이 만료되어 해제되었습니다.");
	}
}