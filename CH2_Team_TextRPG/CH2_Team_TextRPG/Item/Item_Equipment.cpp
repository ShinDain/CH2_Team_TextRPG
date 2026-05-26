#include "pch.h"
#include "Item_Equipment.h"
#include "Effect/Effect.h"

Item_Equipment::Item_Equipment(const ItemData* InData, const FEquipmentItemData* InEquipmentData)
	:Item(InData), EquipmentData(InEquipmentData)
{
}

void Item_Equipment::Active(Object* Instigator, std::vector<Object*> Targets)
{
	GLog.AddLog("[Item_Equipment] It's not usable item.");
}

void Item_Equipment::OnEquip(Object* Owner)
{
	for (Effect* effect : Effects)
	{
		effect->Apply(Owner, std::vector<Object*>{Owner});
	}
}

void Item_Equipment::OnUnequip(Object* Owner)
{
	for (Effect* effect : Effects)
	{
		//effect->Cancel(Owner, std::vector<Object*>{Owner});
	}
}
