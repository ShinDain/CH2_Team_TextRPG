#pragma once

#include "nlohmann/json.hpp"

enum class EItemCategory
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