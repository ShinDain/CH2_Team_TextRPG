#include "pch.h"
#include "Effect_Poison.h"
#include "Character/Component/EffectComponent.h"
#include "Character/Component/ResourceComponent.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"

Effect_Poison::Effect_Poison(int InValue) : Effect(Game::EffectTag::Debuff::Poison, InValue)
{
}

void Effect_Poison::Apply(Object* Instigator, std::vector<Object*> Targets)
{
	for (Object* Target : Targets)
	{
		auto effectComp = Target->FindComponent<EffectComponent>("Effect");
		if (effectComp && !effectComp->HasActiveEffect(this))
		{
			effectComp->AddActiveEffect(this, Instigator, Duration);
			GLog.AddLog(Target->GetName() + "이(가) 독에 감염되었습니다! (" + std::to_string(Duration) + "턴)");
		}
		else
		{
			auto TargetHP = Target->FindComponent<ResourceComponent>("Resource");
			if (TargetHP)
			{
				TargetHP->Decrease(EResourceType::Health, Value);
				GLog.AddLog("[독] " + Target->GetName() + "이(가) 독으로 인해 " + std::to_string(Value) + "의 피해를 입었습니다!");
			}
		}
	}
}

void Effect_Poison::Remove(Object* Instigator, std::vector<Object*> Targets)
{
	for (Object* Target : Targets)
	{
		GLog.AddLog(Target->GetName() + "의 독 지속시간이 만료되어 해제되었습니다.");
	}
}
