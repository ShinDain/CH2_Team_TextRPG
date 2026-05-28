#pragma once
#include "NPC.h"
#include "Character/Interface/Trade.h"

struct FInventoryEntry;
struct ItemData;

class Merchant : public NPC , public ITrade
{
	const int MERCHANT_SPECIAL_ITEM_BASIC_CNT = 3;

public:
	Merchant();
	virtual ~Merchant() override;

	bool Initialize() override;
	virtual bool Trade(ITrade* Buyer, ITrade* Seller, int ItemId, int Price);

	void RestoreItemList();
	void ClearItemList();

	const std::vector<FInventoryEntry> GetInventoryItemList();

private:
	const ItemData* RandomSpecialItem();

	// ITrade's interface
public:
	virtual bool CanAfford(int Price) override;
	virtual void ModifyGold(int Value) override;

	virtual std::shared_ptr<class InventoryComponent> GetInventory() override;

private:
	std::vector<const ItemData*> SteadySellers;
	int SpecialItemCnt;
};

