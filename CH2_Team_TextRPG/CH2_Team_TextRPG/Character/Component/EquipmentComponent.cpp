#include "pch.h"
#include "EquipmentComponent.h"

EquipmentComponent::EquipmentComponent(Object* InOwner) :
	Component(InOwner, "Equipment")
{
	
}

EquipmentComponent::~EquipmentComponent()
{
	
}

bool EquipmentComponent::Initialize()
{
	// Not Implement.
	return false;
}
