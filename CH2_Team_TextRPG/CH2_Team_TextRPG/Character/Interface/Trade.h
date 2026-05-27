#pragma once

class InventoryComponent;

class ITrade
{
public:
	virtual ~ITrade() = default;

	virtual bool CanAfford(int Price) = 0;
	virtual void ModifyGold(int Value) = 0;

	virtual InventoryComponent* GetInventory() = 0;
};

