#include "pch.h"
#include "HealthComponent.h"

HealthComponent::HealthComponent(Object* InOwner, const class StatComponent* InStat) :
	Component(InOwner, "Health")
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Initialize()
{
	// Not Implement.
}
