#include "pch.h"
#include "EffectComponent.h"

EffectComponent::EffectComponent(Object* InOwner) :
	Component(InOwner, "Effect")
{
}

EffectComponent::~EffectComponent()
{
}

void EffectComponent::UpdateEffects()
{

}

void EffectComponent::RemoveExpiredEffects()
{

}

bool EffectComponent::Initialize()
{
	return false;
}
