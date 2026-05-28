#include "pch.h"
#include "ShopItemProvider.h"
#include "Data/Table/ItemDataTable.h"
#include "Enum/EItemType.h"

#include <algorithm>
#include <random>

namespace
{
constexpr int MaxItemCountPerCategory = 4;
}

std::vector<const ItemData*> ShopItemProvider::BuildShopItems()
{
	std::vector<const ItemData*> ConsumableItems;
	std::vector<const ItemData*> EquipmentItems;

	const std::vector<const ItemData*> ItemDatas = ItemDataTable::GetInstance().GetItemDatas();
	for (const ItemData* Data : ItemDatas)
	{
		if (Data == nullptr)
		{
			continue;
		}

		if (Data->Category == EItemCategory::Consumable)
		{
			ConsumableItems.push_back(Data);
		}
		else if (Data->Category == EItemCategory::Equipment)
		{
			EquipmentItems.push_back(Data);
		}
	}

	std::vector<const ItemData*> ShopItems;
	AppendRandomItems(ShopItems, ConsumableItems, MaxItemCountPerCategory);
	AppendRandomItems(ShopItems, EquipmentItems, MaxItemCountPerCategory);
	return ShopItems;
}

void ShopItemProvider::ShuffleItems(std::vector<const ItemData*>& Items)
{
	static std::random_device RandomDevice;
	static std::mt19937 Generator(RandomDevice());

	std::shuffle(Items.begin(), Items.end(), Generator);
}

void ShopItemProvider::AppendRandomItems(
	std::vector<const ItemData*>& OutShopItems,
	std::vector<const ItemData*> CandidateItems,
	int MaxCount
)
{
	ShuffleItems(CandidateItems);

	const int CandidateCount = static_cast<int>(CandidateItems.size());
	const int SelectCount = CandidateCount < MaxCount ? CandidateCount : MaxCount;
	for (int i = 0; i < SelectCount; i++)
	{
		OutShopItems.push_back(CandidateItems[i]);
	}
}
