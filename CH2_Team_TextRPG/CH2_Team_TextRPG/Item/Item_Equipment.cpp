#include "pch.h"
#include "Item_Equipment.h"

Item_Equipment::Item_Equipment(const ItemData* InData, const FEquipmentItemData* InEquipmentData)
	:Item(InData), EquipmentData(InEquipmentData)
{
}

void Item_Equipment::Active(Object* Instigator, std::vector<Object*> Targets)
{
	GLog.AddLog("[Item_Equipment] It's not usable item.");
}
