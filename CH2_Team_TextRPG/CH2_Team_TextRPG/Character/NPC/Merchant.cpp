#include "pch.h"
#include "Merchant.h"
#include "Character/Component/InventoryComponent.h"
#include "Data/Table/ItemDataTable.h"
#include "Item/ItemData.h"

const std::vector<std::string> SteadySellerItemNames = {
	"하급 체력 포션", "하급 마나 포션", "화염 병"
};

Merchant::Merchant()
	: NPC(), SteadySellers{}, SpecialItemCnt(MERCHANT_SPECIAL_ITEM_BASIC_CNT)
{
}

Merchant::~Merchant()
{
}

bool Merchant::Initialize()
{
	NPC::Initialize();

	for (const std::string& itemName : SteadySellerItemNames)
	{
		const ItemData* data = FindItemDataByName(itemName);
		SteadySellers.push_back(data);
	}

    return false;
}

bool Merchant::CanAfford(int Price)
{
	// Merchant always can afford.
	return true;    
}

void Merchant::ModifyGold(int Value)
{
	// Merchant don't need more gold.
	return;
}

std::shared_ptr<InventoryComponent> Merchant::GetInventory()
{
	std::shared_ptr<InventoryComponent> inventoryComp = FindComponent<InventoryComponent>("Inventory");
	if (inventoryComp == nullptr)
	{
		GLog.AddLog(__FUNCTION__);
		GLog.AddLog("Need InventoryComponent. Npc must have inventoryComponent.");
		return nullptr;
	}

    return inventoryComp;
}

bool Merchant::Trade(ITrade* Buyer, ITrade* Seller, int ItemId, int Price)
{
	std::shared_ptr<InventoryComponent> buyerInventory = Buyer->GetInventory();
	std::shared_ptr<InventoryComponent> sellerInventory = Seller->GetInventory();

	if (buyerInventory && sellerInventory)
	{
		if (sellerInventory->HaveItem(ItemId)
			&& Buyer->CanAfford(Price))
		{
			Seller->ModifyGold(Price);
			sellerInventory->RemoveItem(ItemId);

			Buyer->ModifyGold(-Price);
			buyerInventory->AcquireItem(ItemId);

			return true;
		}
	}

	GLog.AddLog(__FUNCTION__);
	GLog.AddLog(" Trade failed");

	return false;
}

void Merchant::RestoreItemList()
{
	std::shared_ptr<InventoryComponent> inventory = GetInventory();
	if (inventory)
	{
		ClearItemList();
		for (const ItemData* data : SteadySellers)
		{
			inventory->AcquireItem(data->Id, 99);
		}

		int curSpecialItemCnt = 0;
		while (curSpecialItemCnt < SpecialItemCnt)
		{
			const ItemData* data = RandomSpecialItem();
			if (inventory->HaveItem(data->Id))
				continue;

			inventory->AcquireItem(data->Id);

			++curSpecialItemCnt;
		}
	}
}

void Merchant::ClearItemList()
{
	std::shared_ptr<InventoryComponent> inventory = GetInventory();
	if (inventory)
	{
		inventory->ClearItemList();
	}
}

const std::vector<FInventoryEntry> Merchant::GetInventoryItemList()
{
	std::shared_ptr<InventoryComponent> inventory = GetInventory();
	if(inventory)
	{
		return inventory->GetItemList();
	}

	return {};
}

const ItemData* Merchant::RandomSpecialItem()
{
	const std::vector<const ItemData*> itemDatas = ItemDataTable::GetInstance().GetItemDatas();

	if (itemDatas.empty())
		return nullptr;

	size_t itemCnt = itemDatas.size();
	int randNum = rand() % itemCnt;

	return itemDatas[randNum];
}
