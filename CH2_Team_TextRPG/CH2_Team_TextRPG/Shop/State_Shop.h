#pragma once
#include "Core/State.h"
#include "Character/NPC/Merchant.h"

namespace Shop
{
	enum class EActionType
	{
		Buy,
		Sell,
		Inventory,
		Exit,
		End,
	};
}

class State_Shop : public BaseState
{
public:
	State_Shop();
protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	Shop::EActionType ShowShopMenu();
	void ShowShopItemList();
	void ShowPlayerItemList();
	void ShowPlayerInventory();

	void HandleShopAction();

	void HandleBuyAction();
	void HandleSellAction();
	void HandleInventoryAction();

private:
	Merchant MerchantInstance;
	Shop::EActionType CurrentAction;
};

