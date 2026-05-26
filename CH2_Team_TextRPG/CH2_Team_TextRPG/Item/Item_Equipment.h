#pragma once
#include "Item/Item.h"
#include "ItemData.h"

class Item_Equipment : public Item
{
	friend class EquipmentComponent;

public:
	Item_Equipment(const ItemData* InData, const FEquipmentItemData* InEquipmentData);

	virtual void Active(Object* Instigator, std::vector<Object*> Targets) override;

private:
	virtual void OnEquip(Object* Owner);
	virtual void OnUnequip(Object* Owner);

	const FEquipmentItemData* GetEquipmentData() { return EquipmentData; }
private:
	const FEquipmentItemData* EquipmentData;
};

