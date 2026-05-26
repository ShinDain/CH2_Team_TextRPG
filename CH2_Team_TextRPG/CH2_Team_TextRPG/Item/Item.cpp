#include "pch.h"
#include "Item.h"
#include "Effect/Effect.h"

Item::Item(const ItemData* InData)
	:Data(InData)
{
}

Item::~Item()
{
	for (Effect* effect : Effects)
	{
		delete effect;
		effect = nullptr;
	}
}

void Item::Active(Object* Instigator)
{
	if (Instigator == nullptr)
		return;

	for (Effect* effect : Effects)
	{
		effect->Apply(Instigator);
	}
}

void Item::AddEffect(Effect* InEffect)
{
	if (InEffect)
	{
		Effects.emplace_back(InEffect);
	}
}
