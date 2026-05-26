#pragma once

#include "nlohmann/json.hpp"

enum class Category
{
	Equipment = 0,
	Consumable,
	Ingredient,
	None,
};

NLOHMANN_JSON_SERIALIZE_ENUM(Category, {
	{Category::Equipment, "Equipment"},
	{Category::Consumable, "Consumable"},
	{Category::Ingredient, "Ingredient"}
	});