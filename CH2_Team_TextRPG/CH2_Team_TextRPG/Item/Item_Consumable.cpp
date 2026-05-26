#include "pch.h"
#include "Item_Consumable.h"
#include "Effect/Effect.h"

Item_Consumable::Item_Consumable(const ItemData* InData, const FConsumableItemData* InConsumableItemData)
	:Item(InData), ConsumableItemData(InConsumableItemData)
{
}

void Item_Consumable::Active(Object* Instigator, std::vector<class Object*> Targets)
{
	if (Instigator == nullptr)
		return;

	for (Effect* effect : Effects)
	{
		if (effect == nullptr)
			continue;

		effect->Apply(Instigator, Targets);
	}
}
