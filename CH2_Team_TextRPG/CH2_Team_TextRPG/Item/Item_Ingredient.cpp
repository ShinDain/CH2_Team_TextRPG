#include "pch.h"
#include "Item_Ingredient.h"

Item_Ingredient::Item_Ingredient(const ItemData* InData)
	:Item(InData)
{
}

void Item_Ingredient::Active(Object* Instigator, std::vector<class Object*> Targets)
{
	GLog.AddLog("[Item_Ingredient] It's not usable item.");
}
