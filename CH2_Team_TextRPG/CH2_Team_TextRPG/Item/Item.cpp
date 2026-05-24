#include "pch.h"
#include "Item.h"
#include "Effect/Effect.h"

Item::Item(const ItemData* InData)
{
}

Item::~Item()
{
	for (IEffect* effect : Effects)
	{
		delete effect;
		effect = nullptr;
	}
}

void Item::Active(Object* Instigator)
{
	for (IEffect* effect : Effects)
	{
		effect->Apply(Instigator);
	}
}
