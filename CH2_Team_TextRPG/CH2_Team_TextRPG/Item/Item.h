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

	virtual void Active(Object* Instigator, std::vector<Object*> Targets) = 0;

	virtual void AddEffect(Effect* InEffect);

	const ItemData* GetItemData() const { return Data; }
	std::vector<Effect*> GetEffects() const { return Effects; }
	
	const std::string& GetName() const { return Data->Name; }
	int GetPrice() const { return Data->Price; }
	int GetId() const { return Data->Id; }
protected:
	const ItemData* Data;
	std::vector<Effect*> Effects;
};

