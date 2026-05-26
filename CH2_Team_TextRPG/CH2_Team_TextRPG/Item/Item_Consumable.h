#pragma once

#include "Item/Item.h"
#include "Enum/EEffect.h"
#include "Effect/EffectData.h"

struct FConsumableItemData
{
	ETargetType TargetType;
	std::vector<EffectData> EffectDatas;
};

class Item_Consumable : public Item
{
public:
	Item_Consumable(const ItemData* InData, const FConsumableItemData* InConsumableItemData);
	
	virtual void Active(class Object* Instigator, std::vector<class Object*> Targets) override;

private:
	const FConsumableItemData* ConsumableItemData;

};

