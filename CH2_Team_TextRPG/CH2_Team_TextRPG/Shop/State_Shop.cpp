#include "pch.h"
#include "State_Shop.h"
#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Data/Table/ItemDataTable.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "Shop/ShopItemProvider.h"
#include "UI/ShopScreen.h"

State_Shop::State_Shop()
{
	Name = "Shop";
}

void State_Shop::Enter()
{
	CurrentMode = EShopScreenMode::ItemList;
	SelectedItemIndex = -1;
	LastMessage.clear();
	ShopItems = ShopItemProvider::BuildShopItems();
	GLog.AddLog("상점에 입장했습니다.");
}

void State_Shop::Process()
{
	Player* MainPlayer = GameInstance::GetInstance().GetMainPlayer();

	switch (CurrentMode)
	{
	case EShopScreenMode::ItemList:
		ProcessItemList(MainPlayer);
		break;
	case EShopScreenMode::ItemDetail:
		ProcessItemDetail(MainPlayer);
		break;
	default:
		CurrentMode = EShopScreenMode::ItemList;
		ProcessItemList(MainPlayer);
		break;
	}
}

void State_Shop::ProcessItemList(Player* MainPlayer)
{
	ShopScreen::Draw(MainPlayer, ShopItems, nullptr, LastMessage, false);

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		LastMessage = "잘못된 상품 번호입니다.";
		return;
	}

	if (Input == 0)
	{
		StateManager::GetInstance().ChangeState(EState::Map);
		return;
	}

	if (Input >= 1 && Input <= static_cast<int>(ShopItems.size()))
	{
		SelectedItemIndex = Input - 1;
		CurrentMode = EShopScreenMode::ItemDetail;
		LastMessage.clear();
		return;
	}

	LastMessage = "잘못된 상품 번호입니다.";
}

void State_Shop::ProcessItemDetail(Player* MainPlayer)
{
	const ItemData* SelectedItem = GetSelectedItem();
	if (SelectedItem == nullptr)
	{
		CurrentMode = EShopScreenMode::ItemList;
		SelectedItemIndex = -1;
		LastMessage = "잘못된 상품 번호입니다.";
		return;
	}

	ShopScreen::Draw(MainPlayer, ShopItems, SelectedItem, LastMessage, true);

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		LastMessage = "잘못된 입력입니다.";
		return;
	}

	if (Input == 0)
	{
		CurrentMode = EShopScreenMode::ItemList;
		SelectedItemIndex = -1;
		LastMessage.clear();
		return;
	}

	if (Input == 1)
	{
		LastMessage = TryBuyItem(MainPlayer, SelectedItemIndex);
		if (LastMessage.find("구매했습니다") != std::string::npos)
		{
			CurrentMode = EShopScreenMode::ItemList;
			SelectedItemIndex = -1;
		}
		return;
	}

	LastMessage = "1 또는 0을 입력해주세요.";
}

void State_Shop::Exit()
{
	ShopItems.clear();
	LastMessage.clear();
	GLog.AddLog("상점을 떠났습니다.");
}

const ItemData* State_Shop::GetSelectedItem() const
{
	if (SelectedItemIndex < 0 || SelectedItemIndex >= static_cast<int>(ShopItems.size()))
	{
		return nullptr;
	}

	return ShopItems[SelectedItemIndex];
}

std::string State_Shop::TryBuyItem(Player* MainPlayer, int ItemIndex) const
{
	if (ItemIndex < 0 || ItemIndex >= static_cast<int>(ShopItems.size()))
	{
		return "잘못된 상품 번호입니다.";
	}

	if (MainPlayer == nullptr)
	{
		return "플레이어 정보를 찾을 수 없습니다.";
	}

	const ItemData* Data = ShopItems[ItemIndex];
	if (Data == nullptr)
	{
		return "상품 정보를 찾을 수 없습니다.";
	}

	if (!MainPlayer->CanAfford(Data->Price))
	{
		return "골드가 부족합니다.";
	}

	MainPlayer->ModifyGold(-Data->Price);
	MainPlayer->AcquireItem(static_cast<int>(Data->Id), 1);
	return Data->Name + "을 구매했습니다.";
}
