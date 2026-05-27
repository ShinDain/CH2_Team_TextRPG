#include "pch.h"
#include "Merchant.h"
#include "Character/Component/InventoryComponent.h"

Merchant::Merchant()
	: NPC()
{
}

Merchant::~Merchant()
{
}

bool Merchant::Initialize()
{
	NPC::Initialize();

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

InventoryComponent* Merchant::GetInventory()
{
	InventoryComponent* inventoryComp = FindComponent<InventoryComponent>("Inventory");
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
	InventoryComponent* buyerInventory = Buyer->GetInventory();
	InventoryComponent* sellerInventory = Seller->GetInventory();

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

std::vector<FTradeItemEntry> Merchant::GetInventoryItemList()
{
	return std::vector<FTradeItemEntry>();
}
