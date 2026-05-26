#include "pch.h"
#include "ItemManager.h"
#include "Data/Table/ItemDataTable.h"
#include "Effect/Factory/EffectFactory.h"
#include "Item/Item.h"
#include "Item/Item_Consumable.h"
#include "Item/Item_Equipment.h"
#include "Item/Item_Ingredient.h"

ItemManager::ItemManager()
{
	CreateItemFuncMap[EItemCategory::Consumable] = &ItemManager::CreateConsumableItemInstance;
	CreateItemFuncMap[EItemCategory::Equipment] = &ItemManager::CreateEquipmentItemInstance;
	CreateItemFuncMap[EItemCategory::Ingredient] = &ItemManager::CreateIngredientItemInstance;
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
	Item* newItem = nullptr;

	EItemCategory category = Data->Category;
	auto createFunc = CreateItemFuncMap.find(category);
	if (createFunc != CreateItemFuncMap.end())
	{
		newItem = (this->*CreateItemFuncMap[category])(Data);
	}
	else
	{
		GLog.AddLog("[ItemManager] Invalid ItemCategory.");
		return nullptr;
	}

	if (newItem)
	{
		std::string Name = Data->Name;
		uint32_t Id = Data->Id;

		Items.emplace_back(newItem);
		NameMap[Name] = newItem;
		IdMap[Id] = newItem;
	}
	
	return newItem;
}

Item* ItemManager::CreateConsumableItemInstance(const ItemData* Data)
{
	const FConsumableItemData* ConsumableData = ConsumableDataTable::GetInstance().FindConsumableDataByIndex(Data->Id);
	if (ConsumableData == nullptr)
		return nullptr;

	Item* newItem = new Item_Consumable(Data, ConsumableData);
	for (const auto& tagData : ConsumableData->EffectDatas)
	{
		Effect* newEffect = EffectFactory::CreateEffect(tagData);
		newItem->AddEffect(newEffect);
	}

	return newItem;
}

Item* ItemManager::CreateEquipmentItemInstance(const ItemData* Data)
{
	const FEquipmentItemData* EquipmentData = EquipmentDataTable::GetInstance().FindEquipmentDataByIndex(Data->Id);
	if (EquipmentData == nullptr)
		return nullptr;

	Item* newItem = new Item_Equipment(Data, EquipmentData);
	for (const auto& tagData : EquipmentData->EffectDatas)
	{
		Effect* newEffect = EffectFactory::CreateEffect(tagData);
		newItem->AddEffect(newEffect);
	}

	return newItem;
}

Item* ItemManager::CreateIngredientItemInstance(const ItemData* Data)
{
	Item* newItem = new Item_Ingredient(Data);

	return newItem;
}
