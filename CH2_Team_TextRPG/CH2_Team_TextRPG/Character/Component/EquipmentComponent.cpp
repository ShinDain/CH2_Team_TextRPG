#include "pch.h"
#include "EquipmentComponent.h"
#include "Item/Item_Equipment.h"
#include "Data/Table/ItemDataTable.h"

EquipmentComponent::EquipmentComponent(Object* InOwner) :
	Component(InOwner, "Equipment")
{
	
}

EquipmentComponent::~EquipmentComponent()
{
	
}

bool EquipmentComponent::Initialize()
{
	return true;
}

void EquipmentComponent::OnEquip(Item_Equipment* InEquipment)
{
	if (InEquipment == nullptr)
		return;

	EEquipmentType equipmentType = InEquipment->GetEquipmentData()->EquipmentType;
	if (EquipmentSlots[equipmentType] != nullptr)
	{
		OnUnequip(equipmentType);
	}

	EquipmentSlots[equipmentType] = InEquipment;
	InEquipment->OnEquip(Owner);
}

const ItemData* EquipmentComponent::OnUnequip(EEquipmentType Type)
{
	const ItemData* retData = nullptr;
	if (EquipmentSlots[Type] != nullptr)
	{
		retData = EquipmentSlots[Type]->GetItemData();

		EquipmentSlots[Type]->OnUnequip(Owner);
		EquipmentSlots[Type] = nullptr;
	}

	return retData;
}
