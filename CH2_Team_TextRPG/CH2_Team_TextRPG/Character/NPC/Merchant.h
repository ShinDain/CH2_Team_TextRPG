#pragma once
#include "NPC.h"
#include "Character/Interface/Trade.h"

struct FTradeItemEntry
{
	int Id;
	std::string Name;
	int Price;
};

class Merchant : public NPC , public ITrade
{
public:
	Merchant();
	virtual ~Merchant() override;

	bool Initialize() override;
	virtual bool Trade(ITrade* Buyer, ITrade* Seller, int ItemId, int Price);

	std::vector<FTradeItemEntry> GetInventoryItemList();

	// ITrade's interface
public:
	virtual bool CanAfford(int Price) override;
	virtual void ModifyGold(int Value) override;

	virtual InventoryComponent* GetInventory() override;

};

