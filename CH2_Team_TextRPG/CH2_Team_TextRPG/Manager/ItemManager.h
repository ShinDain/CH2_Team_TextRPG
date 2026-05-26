#pragma once
#include "Item/Item.h"
#include "Enum/EItemType.h"

class ItemManager
{
	using CreateItemFunc = Item * (ItemManager::*)(const ItemData*);

public:
	ItemManager();
	~ItemManager();

	static ItemManager& GetInstance();

	Item* FindItemByName(const std::string& Name);
	Item* FindItemById(uint32_t Id);

private:
	Item* CreateItemInstance(const ItemData* Data);

	Item* CreateConsumableItemInstance(const ItemData* Data);
	Item* CreateEquipmentItemInstance(const ItemData* Data);
	Item* CreateIngredientItemInstance(const ItemData* Data);
private:
	std::vector<Item*> Items;

	std::unordered_map<std::string, Item*> NameMap;
	std::unordered_map<uint32_t, Item*> IdMap;

	std::unordered_map<EItemCategory, CreateItemFunc> CreateItemFuncMap;
};

inline Item* FindItemByName(const std::string& Name)
{
	return ItemManager::GetInstance().FindItemByName(Name);
}

inline Item* FindItemById(uint32_t Id)
{
	return ItemManager::GetInstance().FindItemById(Id);
}