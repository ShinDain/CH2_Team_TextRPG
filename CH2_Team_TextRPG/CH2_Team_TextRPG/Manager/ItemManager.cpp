#include "pch.h"
#include "ItemManager.h"
#include "Data/Table/ItemDataTable.h"
#include "Effect/Factory/EffectFactory.h"
#include "Item/Item.h"

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
	for (Item* item : Items)
	{
		delete item;
		item = nullptr;
	}

	Items.clear();
	NameMap.clear();
	IdMap.clear();
}

ItemManager& ItemManager::GetInstance()
{
	static ItemManager Instance;
	return Instance;
}

Item* ItemManager::FindItemByName(const std::string& Name)
{
	if (NameMap.find(Name) == NameMap.end())
	{
		const ItemData* Data = FindItemDataByName(Name);
		Item* newItem = CreateItemInstance(Data);

		return newItem;
	}
	else
	{
		auto iter = NameMap.find(Name);
		return iter->second;
	}

	return nullptr;
}

Item* ItemManager::FindItemById(uint32_t Id)
{
	if (IdMap.find(Id) == IdMap.end())
	{
		const ItemData* Data = FindItemDataById(Id);
		Item* newItem = CreateItemInstance(Data);

		return newItem;
	}
	else
	{
		auto iter = IdMap.find(Id);
		return iter->second;
	}

	return nullptr;
}

Item* ItemManager::CreateItemInstance(const ItemData* Data)
{
//	Item* newItem = new Item(Data);
//	
//	if (newItem)
//	{
//		for (const auto& tagData : Data->EffectDatas)
//		{
//			Effect* newEffect = EffectFactory::CreateEffect(tagData);
//			newItem->AddEffect(newEffect);
//		}
//
//		std::string Name = Data->Name;
//		uint32_t Id = Data->Id;
//
//		Items.emplace_back(newItem);
//		NameMap[Name] = newItem;
//		IdMap[Id] = newItem;
//	}
	
	return nullptr;
}
