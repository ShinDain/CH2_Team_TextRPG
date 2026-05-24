#pragma once

#include "Data/Table/ItemDataTable.h"

class Object;
class IEffect;

class Item
{
public:
	Item() = delete;
	Item(const ItemData* InData);
	virtual ~Item();

	virtual void Active(Object* Instigator);

private:
	const ItemData* Data;
	std::vector<IEffect*> Effects;
};

