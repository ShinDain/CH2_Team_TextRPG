#pragma once

#include <string>

struct ItemData;

class ShopItemDescriptionBuilder
{
public:
	static std::string BuildDescription(const ItemData* Item);
};
