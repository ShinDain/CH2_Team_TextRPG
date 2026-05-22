#include "pch.h"
#include "ItemDataTable.h"

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
