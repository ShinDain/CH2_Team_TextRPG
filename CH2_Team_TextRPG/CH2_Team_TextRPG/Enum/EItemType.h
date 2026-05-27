#pragma once

#include "nlohmann/json.hpp"

enum class EItemCategory : uint8_t
{
	Equipment = 0,
	Consumable,
	Ingredient,
	None,
};

NLOHMANN_JSON_SERIALIZE_ENUM(EItemCategory, {
	{EItemCategory::Equipment, "Equipment"},
	{EItemCategory::Consumable, "Consumable"},
	{EItemCategory::Ingredient, "Ingredient"}
	});

enum class EConsumableTime
{
	Always,
	InCombat,
	End,
};

NLOHMANN_JSON_SERIALIZE_ENUM(EConsumableTime, {
	{EConsumableTime::Always, "Always"},
	{EConsumableTime::InCombat, "InCombat"}
	});

enum class EEquipmentType
{
	Head = 0,
	Body,
	Gloves,
	Shoes,
	Ring,
	Weapon,
	End
};

NLOHMANN_JSON_SERIALIZE_ENUM(EEquipmentType, {
	{EEquipmentType::Head, "Head"},
	{EEquipmentType::Body, "Body"},
	{EEquipmentType::Gloves, "Gloves"},
	{EEquipmentType::Shoes, "Shoes"},
	{EEquipmentType::Ring, "Ring"},
	{EEquipmentType::Weapon, "Weapon"}
	});
