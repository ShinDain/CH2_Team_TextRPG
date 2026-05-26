#pragma once

#include "Item/Item.h"
#include "ItemData.h"

class Item_Consumable : public Item
{
public:
	Item_Consumable(const ItemData* InData, const FConsumableItemData* InConsumableItemData);
	
	virtual void Active(class Object* Instigator, std::vector<class Object*> Targets) override;

	const FConsumableItemData* GetConsumableData() { return ConsumableData; }
private:
	const FConsumableItemData* ConsumableData;

};

