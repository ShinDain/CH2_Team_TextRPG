#pragma once
#include "DataTable.h"

struct ItemData
{
	std::string Name;
	int Price;
	uint32_t Id;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ItemData, Name, Price, Id);

class ItemDataTable final : public BaseDataTable
{
private:
	ItemDataTable() {};
public:
	~ItemDataTable();

	static ItemDataTable& GetInstance();

	const ItemData* FindItemDataByName(const std::string& Name) const;
	const ItemData* FindItemDataByIndex(uint32_t Index) const;

protected:
	virtual void ParseData(const json& InData) override;

private:
	std::vector<const ItemData*> ItemDatas;

	std::unordered_map<std::string, const ItemData*> NameMap;
	std::unordered_map<uint32_t, const ItemData*> IndexMap;
};

inline const ItemData* FindItemDataByName(const std::string& Name)
{
	return ItemDataTable::GetInstance().FindItemDataByName(Name);
}

inline const ItemData* FindItemDataByIndex(uint32_t Index)
{
	return ItemDataTable::GetInstance().FindItemDataByIndex(Index);
}
