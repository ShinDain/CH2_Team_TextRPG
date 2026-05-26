#include "pch.h"
#include "EffectComponent.h"
#include "Effect/Effect.h"
#include <algorithm>

EffectComponent::EffectComponent(Object* InOwner) :
	Component(InOwner, "Effect")
{
}

EffectComponent::~EffectComponent()
{
}

void EffectComponent::AddActiveEffect(Effect* InEffect, Object* InCaster, int InDuration)
{
	if (InEffect && InDuration > 0)
	{
		ActiveEffects.push_back({ InEffect, InCaster, InDuration });
	}
}

void EffectComponent::UpdateEffects()
{
	// TODO : 버프/디버프일시 턴수만 감소하게 수정필요
	for (FActiveEffect& activeEffect : ActiveEffects)
	{
		if (activeEffect.RemainingDuration > 0)
		{
			std::vector<Object*> target = { Owner };
			activeEffect.EffectPtr->Apply(activeEffect.Caster, target);
			activeEffect.RemainingDuration--;
		}
	}
}

void EffectComponent::RemoveExpiredEffects()
{
	auto it = std::remove_if(ActiveEffects.begin(), ActiveEffects.end(),
		[](const FActiveEffect& effect) {
			return effect.RemainingDuration <= 0;
		});
	ActiveEffects.erase(it, ActiveEffects.end());
}

bool EffectComponent::Initialize()
{
	return true;
}
