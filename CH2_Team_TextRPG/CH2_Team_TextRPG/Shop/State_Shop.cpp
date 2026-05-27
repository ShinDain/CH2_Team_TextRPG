#include "pch.h"
#include "State_Shop.h"
#include "ShopCondition.h"
#include "Core/GameInstance.h"
#include "Character/Player/Player.h"
#include "Character/NPC/Merchant.h"
#include "Manager/InputManager.h"
#include "Manager/ObjectManager.h"
#include "Item/Item.h"
#include "Character/Component/InventoryComponent.h"
#include "Character/Component/EquipmentComponent.h"
#include "Enum/EItemType.h"

State_Shop::State_Shop()
{
	AddTransition<ShopCondition>(EState::Map);
	CurrentAction = Shop::EActionType::Menu;

	MerchantInstance = CreateObject<Merchant>();
}

void State_Shop::Enter()
{
	MerchantInstance->RestoreItemList();
	CurrentAction = Shop::EActionType::Menu;
	GInput << "\n상인이 반갑게 맞이합니다.\n";
}

void State_Shop::Process()
{
	switch (CurrentAction)
	{
	case Shop::EActionType::Menu:
	{
		CurrentAction = ShowShopMenu();
	}
	break;
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

void State_Shop::Exit()
{
	MerchantInstance->ClearItemList();
	GInput << "상점을 떠납니다.\n";
}

Shop::EActionType State_Shop::ShowShopMenu()
{
	int input = -1;

	GInput << "\n어떤 행동을 하시겠습니까?\n1. 구매\n2. 판매\n3. 인벤토리\n4. 나가기\n";
	GInput >> input;

	if (GInput.IsFailed() || input < 1 || input >(int)Shop::EActionType::End)
	{
		GInput << "유효하지 않은 입력입니다. 다시 입력해주세요.\n";
		return Shop::EActionType::Menu;
	}

	return static_cast<Shop::EActionType>(input);
}

void State_Shop::HandleBuyAction()
{
	Player* mainPlayer = GetMainPlayer();
	if (mainPlayer == nullptr)
		return;

	GInput << "\n 상인의 판매 아이템 리스트\n";

	ITrade* buyer = dynamic_cast<ITrade*>(mainPlayer);
	ITrade* seller = dynamic_cast<ITrade*>(MerchantInstance);

	if (seller && buyer)
	{
		HandleTrade(buyer, seller);
	}

	GInput << "플레이어 현재 Gold : " << mainPlayer->GetInventory()->GetOwnedGold();
}

void State_Shop::HandleSellAction()
{
	Player* mainPlayer = GetMainPlayer();
	if (mainPlayer == nullptr)

	GInput << "\n판매 가능한 플레이어 아이템 리스트\n";

	ITrade* buyer = dynamic_cast<ITrade*>(MerchantInstance);
	ITrade* seller = dynamic_cast<ITrade*>(mainPlayer);

	if (seller && buyer)
	{
		HandleTrade(buyer, seller);
	}

	GInput << "플레이어 현재 Gold : " << mainPlayer->GetInventory()->GetOwnedGold() << "G\n";
}

void State_Shop::HandleInventoryAction()
{
	//Player* mainPlayer = GetMainPlayer();

	//std::vector<FInventoryEntry> itemList = mainPlayer->GetInventory()->GetItemList();
	//GInput << "\n 장착중인 플레이어 아이템\n";


	//int idx = 1;
	//for (FInventoryEntry entry : itemList)
	//{
	//	int sellPrice = (float)(entry.ItemInstance->GetPrice()) * 0.6f;

	//	GInput << idx << ". " << entry.ItemInstance->GetName() << " " << entry.Amount << "개, 개당 판매가 " << sellPrice << "G\n";
	//	++idx;
	//}
	CurrentAction = Shop::EActionType::Menu;
}

void State_Shop::HandleTrade(ITrade* Buyer, ITrade* Seller)
{
	std::vector<std::pair<int, int>> sellerItemList = {};
	std::vector<FInventoryEntry> sellList = Seller->GetInventory()->GetItemList();
	
	int idx = 1;
	for (FInventoryEntry entry : sellList)
	{
		int sellPrice = entry.ItemInstance->GetPrice();
		sellerItemList.emplace_back(std::make_pair(entry.Id, sellPrice));
		GInput << idx << ". " << entry.ItemInstance->GetName() << " " << entry.Amount << "개, " << entry.ItemInstance->GetPrice() << "G\n";
		++idx;
	}
	GInput << idx << ". " << "뒤로 가기\n";

	int exitIdx = idx;

	int input = -1;
	GInput >> input;

	if (GInput.IsFailed() || input < 1 || input > exitIdx)
	{
		GInput << "유효하지 않은 입력입니다. 다시 입력해주세요.\n";
		return;
	}

	if (input == exitIdx)
	{
		CurrentAction = Shop::EActionType::Menu;
	}
	else
	{
		int sellItemId = sellerItemList[input - 1].first;
		int sellItemPrice = sellerItemList[input - 1].second;

		if (MerchantInstance->Trade(Buyer, Seller, sellItemId, sellItemPrice))
		{
			GInput << "거래에 성공했습니다.\n";
		}
		else
		{
			GInput << "거래에 실패했습니다. 다시 시도해주세요.\n";
		}
	}
}
