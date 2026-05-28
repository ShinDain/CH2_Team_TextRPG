#pragma once

#include <vector>

struct ItemData;

class ShopItemProvider
{
public:
	static std::vector<const ItemData*> BuildShopItems();

private:
	static void ShuffleItems(std::vector<const ItemData*>& Items);
	static void AppendRandomItems(
		std::vector<const ItemData*>& OutShopItems,
		std::vector<const ItemData*> CandidateItems,
		int MaxCount
	);
};
