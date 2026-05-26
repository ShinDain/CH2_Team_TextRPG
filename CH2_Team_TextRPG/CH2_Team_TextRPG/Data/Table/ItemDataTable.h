#pragma once
#include "DataTable.h"
#include "Enum/EItemType.h"
#include "Enum/EEffect.h"
#include "Manager/InputManager.h"
#include "Effect/EffectData.h"

struct ItemData
{
public:
	std::string Name;
	int Price;
	uint32_t Id;
	EItemCategory Category;
	ETargetType TargetType;
	std::vector<EffectData> EffectDatas;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ItemData, Name, Price, Id, Category, EffectDatas);

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

inline const ItemData* FindItemDataById(uint32_t Index)
{
	return ItemDataTable::GetInstance().FindItemDataByIndex(Index);
}
