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
			GInput << " [" << Target->GetName() << "]이(가) 독에 감염되었습니다! (" << Duration << "턴)\n";
		}
		else
		{
			auto TargetHP = Target->FindComponent<ResourceComponent>("Resource");
			if (TargetHP)
			{
				TargetHP->Decrease(EResourceType::Health, Value);
				GInput << "[독] " << Target->GetName() << "이(가) 독으로 인해 " << Value << "의 피해를 입었습니다!\n";
			}
		}
	}
}

void Effect_Poison::Remove(Object* Instigator, std::vector<Object*> Targets)
{
	for (Object* Target : Targets)
	{
		GInput << " [" << Target->GetName() << "]의 독 지속시간이 만료되어 해제되었습니다.\n";
	}
}
