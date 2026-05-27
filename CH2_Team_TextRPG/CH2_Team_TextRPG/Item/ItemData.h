#pragma once
#include "Data/Character/Stat.h"

// Consumable Item Data
struct FConsumableItemData
{
	int Id;
	ETargetType TargetType;
	uint32_t Duration;
	std::vector<EffectData> EffectDatas;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FConsumableItemData, Id, TargetType, Duration, EffectDatas);

// Equipment Item Data
struct FEquipmentItemData
{
	int Id;
	EEquipmentType EquipmentType;
	std::vector<EffectData> EffectDatas;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FEquipmentItemData, Id, EquipmentType, EffectDatas);
