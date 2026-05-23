#include "pch.h"
#include "StatComponent.h"

StatComponent::StatComponent(Object* InOwner) :
	Component(InOwner, "Stat")
{
}

StatComponent::~StatComponent()
{
	
}

bool StatComponent::Initialize()
{
	// Not Implement.
	return false;
}
