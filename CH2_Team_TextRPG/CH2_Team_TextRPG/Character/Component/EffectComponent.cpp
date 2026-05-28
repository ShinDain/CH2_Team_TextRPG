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

EActiveEffectType EffectComponent::DetermineEffectType(const std::string& InTag) const
{
	// 기절, 무적
	if (InTag.rfind("CC", 0) == 0 || InTag.find("Invincible") != std::string::npos)
	{
		return EActiveEffectType::State;
	}
	
	// 버프, 디버프
	if (InTag.rfind("Stat.", 0) == 0 || InTag.rfind("Buff_", 0) == 0 || InTag.rfind("Debuff_Stat", 0) == 0)
	{
		return EActiveEffectType::Duration;
	}

	// 화상, 독
	return EActiveEffectType::Periodic;
}

void EffectComponent::AddActiveEffect(Effect* InEffect, Object* InCaster, int InDuration)
{
	if (InEffect && InDuration > 0)
	{
		EActiveEffectType EffectType = DetermineEffectType(InEffect->GetTag());
		ActiveEffects.push_back({ InEffect, InCaster, InDuration, EffectType });
	}
}

bool EffectComponent::HasActiveEffect(Effect* InEffect) const
{
	for (const FActiveEffect& activeEffect : ActiveEffects)
	{
		if (activeEffect.EffectPtr == InEffect)
			return true;
	}
	return false;
}

bool EffectComponent::HasEffectByTag(const std::string& InTag) const
{
	for (const FActiveEffect& activeEffect : ActiveEffects)
	{
		if (activeEffect.EffectPtr && activeEffect.EffectPtr->GetTag() == InTag)
			return true;
	}
	return false;
}

void EffectComponent::UpdateEffects()
{
	for (FActiveEffect& activeEffect : ActiveEffects)
	{
		if (activeEffect.RemainingDuration > 0)
		{
			if (activeEffect.Type == EActiveEffectType::Periodic)
			{
				std::vector<Object*> target = { Owner };
				activeEffect.EffectPtr->Apply(activeEffect.Caster, target);
			}
			activeEffect.RemainingDuration--;
		}
	}
}

void EffectComponent::RemoveExpiredEffects()
{
	for (FActiveEffect& effect : ActiveEffects)
	{
		if (effect.RemainingDuration <= 0)
		{
			std::vector<Object*> target = { Owner };
			effect.EffectPtr->Remove(effect.Caster, target);
		}
	}

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
