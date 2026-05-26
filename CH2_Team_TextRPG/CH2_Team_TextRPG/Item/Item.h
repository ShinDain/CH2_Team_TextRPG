#pragma once

#include "Data/Table/ItemDataTable.h"

class Object;
class Effect;

class Item
{
public:
	Item() = delete;
	Item(const ItemData* InData);
	virtual ~Item();

	virtual void Active(Object* Instigator, std::vector<Object*> Targets);

	virtual void AddEffect(Effect* InEffect);

	const ItemData* GetItemData() { return Data; }
	std::vector<Effect*> GetEffects() { return Effects; }
private:
	const ItemData* Data;
	std::vector<Effect*> Effects;
};

