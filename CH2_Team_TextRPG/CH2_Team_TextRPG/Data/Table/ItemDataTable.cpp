#include "pch.h"
#include "ItemDataTable.h"

ItemData::ItemData(const json& Data)
{
	Name = Data["name"];
	Price = Data["price"];
	Id = Data["id"];
}

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
	//if(NameMap)
	return nullptr;
}

const ItemData* ItemDataTable::FindItemDataByIndex(uint32_t Index) const
{
	return nullptr;
}

void ItemDataTable::ParseData(const json& InData)
{
	for (const json& data : InData)
	{
		ItemData* newData = new ItemData(data);
		if (newData)
		{
			ItemDatas.emplace_back(newData);
			NameMap[newData->Name] = newData;
			IndexMap[newData->Id] = newData;
		}
	}
}
