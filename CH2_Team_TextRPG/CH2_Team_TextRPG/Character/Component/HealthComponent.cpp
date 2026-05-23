#include "pch.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent(Object* InOwner, const class StatComponent* InStat) :
	Component(InOwner, "Health")
{
}

HealthComponent::~HealthComponent()
{
}

bool HealthComponent::Initialize()
{
	// Not Implement.
	return false;
}
