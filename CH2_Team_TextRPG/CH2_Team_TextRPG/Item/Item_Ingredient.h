#pragma once
#include "Item/Item.h"
#include "ItemData.h"

class Item_Ingredient : public Item
{
public:
	Item_Ingredient(const ItemData* InData);

	virtual void Active(class Object* Instigator, std::vector<class Object*> Targets) override;
private:

};
