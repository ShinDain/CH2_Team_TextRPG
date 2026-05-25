#pragma once
#include "Item/Item.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	static ItemManager& GetInstance();

	Item* FindItemByName(const std::string& Name);
	Item* FindItemById(uint32_t Id);

private:
	Item* CreateItemInstance(const ItemData* Data);

private:
	std::vector<Item*> Items;

	std::unordered_map<std::string, Item*> NameMap;
	std::unordered_map<uint32_t, Item*> IdMap;
};

inline Item* FindItemByName(const std::string& Name)
{
	return ItemManager::GetInstance().FindItemByName(Name);
}

inline Item* FindItemById(uint32_t Id)
{
	return ItemManager::GetInstance().FindItemById(Id);
}