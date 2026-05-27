#include "pch.h"
#include "State_Shop.h"
#include "ShopCondition.h"
#include "Character/NPC/Merchant.h"
#include "Manager/InputManager.h"
#include "Item/Item.h"
#include "Character/Component/InventoryComponent.h"

State_Shop::State_Shop()
{
	AddTransition<ShopCondition>(EState::Map);
	CurrentAction = Shop::EActionType::End;
}

void State_Shop::Enter()
{
	MerchantInstance.RestoreItemList();
	GInput << "\n상인이 반갑게 맞이합니다.\n";
}

void State_Shop::Process()
{
	CurrentAction = ShowShopMenu();

	HandleShopAction();
}

void State_Shop::Exit()
{
	MerchantInstance.ClearItemList();
	GInput << "상점을 떠납니다.\n";
}

Shop::EActionType State_Shop::ShowShopMenu()
{
	int input = -1;
	while (true)
	{
		GInput << "\n어떤 행동을 하시겠습니까?\n1. 구매\n2. 판매\n3. 인벤토리\n4. 나가기\n";
		GInput >> input;

		if (GInput.IsFailed() || input < 1 || input >= (int)Shop::EActionType::End)
		{
			GInput << "유효하지 않은 입력입니다. 다시 입력해주세요.\n";
			continue;
		}

		return static_cast<Shop::EActionType>(input);
	}
}

void State_Shop::ShowShopItemList()
{
	std::vector<FInventoryEntry> itemList = MerchantInstance.GetInventoryItemList();
	GInput << "\n 판매 리스트\n";
	int idx = 1;
	for (FInventoryEntry entry : itemList)
	{
		GInput << idx << ". " << entry.ItemInstance->GetName() << " " << entry.Amount << "개, " << entry.ItemInstance->GetPrice() << "원\n";
		++idx;
	}
}

void State_Shop::ShowPlayerItemList()
{
	std::vector<FInventoryEntry> itemList = MerchantInstance.GetInventoryItemList();
	GInput << "\n 판매 리스트\n";
	int idx = 1;
	for (FInventoryEntry entry : itemList)
	{
		GInput << idx << ". " << entry.ItemInstance->GetName() << " " << entry.Amount << "개, " << entry.ItemInstance->GetPrice() << "원\n";
		++idx;
	}
}

void State_Shop::ShowPlayerInventory()
{
}

void State_Shop::HandleShopAction()
{
	switch (CurrentAction)
	{
	case Shop::EActionType::Buy:
	{
		HandleBuyAction();
	}
		break;
	case Shop::EActionType::Sell:
	{
		HandleSellAction();
	}
		break;
	case Shop::EActionType::Inventory:
	{
		HandleInventoryAction();
	}
		break;
	case Shop::EActionType::Exit:
	{
		Transitions[EState::Map]->Notify();
	}
	break;
	default:
	{
		GLog.AddLog(__FUNCTION__);
		GLog.AddLog(" Invalid Shop Action.");
	}
		break;
	}
}

void State_Shop::HandleBuyAction()
{
	ShowShopItemList();
}

void State_Shop::HandleSellAction()
{
}

void State_Shop::HandleInventoryAction()
{
}
