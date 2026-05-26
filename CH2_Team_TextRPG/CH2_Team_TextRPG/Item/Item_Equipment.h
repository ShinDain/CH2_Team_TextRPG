#pragma once
#include "Item/Item.h"
#include "Enum/EItemType.h"
#include "Data/Character/Stat.h"

struct FEquipmentStatData
{
	EStatType StatType;
	int Value;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FEquipmentStatData, StatType, Value);

struct FEquipmentItemData
{
	int Id;
	EEquipmentType Type;
	std::vector<FEquipmentStatData> StatDatas;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FEquipmentItemData, Type, StatDatas);

class Item_Equipment : public Item
{
public:
	Item_Equipment(const ItemData* InData, const FEquipmentItemData* InEquipmentData);

	virtual void Active(Object* Instigator, std::vector<Object*> Targets) override;

private:
	const FEquipmentItemData* EquipmentData;
};

