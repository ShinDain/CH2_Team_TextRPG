#include "pch.h"
#include "ItemDataTable.h"
#include "Data/DataLoader.h"

ItemDataTable::~ItemDataTable()
{
	for (auto& data : ItemDatas)
	{
		delete data;
	}

	NameMap.clear();
	IndexMap.clear();
}

ItemDataTable& ItemDataTable::GetInstance()
{
	static ItemDataTable Instance;
	return Instance;
}

const ItemData* ItemDataTable::FindItemDataByName(const std::string& name) const
{
	if (NameMap.find(name) != NameMap.end())
	{
		return NameMap.at(name);
	}
	return nullptr;
}

const ItemData* ItemDataTable::FindItemDataByIndex(uint32_t Index) const
{
	if (IndexMap.find(Index) != IndexMap.end())
	{
		return IndexMap.at(Index);
	}
	return nullptr;
}

bool ItemDataTable::Load(const std::string& FilePath)
{
	json jsonData;
	if (!JsonDataParser::Load(FilePath, jsonData))
	{
		return false;
	}

	std::filesystem::path path(FilePath);
	std::string prefix = path.parent_path().stem().string();
	bool ret = true;

	if (prefix == DATA_CATEGORY_ITEM_CONSUMABLE)
	{
		ConsumableDataTable::GetInstance().ParseData(jsonData);
	}
	else if (prefix == DATA_CATEGORY_ITEM_EQUIPMENT)
	{
		EquipmentDataTable::GetInstance().ParseData(jsonData);
	}
	else
	{
		ParseData(jsonData);
	}

	return ret;
}

void ItemDataTable::ParseData(const json& InData)
{
	for (const json& data : InData)
	{
		ItemData* newData = new ItemData();
		*newData = data;
		if (newData)
		{
			ItemDatas.emplace_back(newData);
			NameMap[newData->Name] = newData;
			IndexMap[newData->Id] = newData;
		}
	}
}

// Consumable Data Table
ConsumableDataTable& ConsumableDataTable::GetInstance()
{
	static ConsumableDataTable Instance;
	return Instance;
}

const FConsumableItemData* ConsumableDataTable::FindConsumableDataByIndex(uint32_t Index) const
{
	if (ConsumableDataMap.find(Index) != ConsumableDataMap.end())
	{
		return ConsumableDataMap.at(Index);
	}
	return nullptr;
}

ConsumableDataTable::~ConsumableDataTable()
{
	for (auto& pair : ConsumableDataMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}

	ConsumableDataMap.clear();
}

void ConsumableDataTable::ParseData(const json& InData)
{
	for (const json& data : InData)
	{
		FConsumableItemData* newData = new FConsumableItemData();
		*newData = data;
		if (newData)
		{
			ConsumableDataMap[newData->Id] = newData;
		}
	}
}

// Equipment Data Table
EquipmentDataTable& EquipmentDataTable::GetInstance()
{
	static EquipmentDataTable Instance;
	return Instance;
}

const FEquipmentItemData* EquipmentDataTable::FindEquipmentDataByIndex(uint32_t Index) const
{
	if (EquipmentDataMap.find(Index) != EquipmentDataMap.end())
	{
		return EquipmentDataMap.at(Index);
	}
	return nullptr;
}

EquipmentDataTable::~EquipmentDataTable()
{
	for (auto& pair : EquipmentDataMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}

	EquipmentDataMap.clear();
}

void EquipmentDataTable::ParseData(const json& InData)
{
	for (const json& data : InData)
	{
		FEquipmentItemData* newData = new FEquipmentItemData();
		*newData = data;
		if (newData)
		{
			EquipmentDataMap[newData->Id] = newData;
		}
	}
}
