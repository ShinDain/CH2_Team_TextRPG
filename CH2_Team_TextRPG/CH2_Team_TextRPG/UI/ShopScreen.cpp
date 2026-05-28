#include "pch.h"
#include "ShopScreen.h"
#include "Character/Component/InventoryComponent.h"
#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Data/Table/ItemDataTable.h"
#include "Enum/EItemType.h"
#include "Manager/InputManager.h"
#include "Shop/ShopItemDescriptionBuilder.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"
#include "UI/GameScreen.h"

namespace
{
int GetPlayerGold(Player* MainPlayer)
{
	if (MainPlayer == nullptr)
	{
		return 0;
	}

	std::shared_ptr<InventoryComponent> Inventory = MainPlayer->GetInventory();
	return Inventory != nullptr ? Inventory->GetOwnedGold() : 0;
}

void DrawShopInventoryPanel(const Player* MainPlayer)
{
	ConsoleRenderer::DrawBox(0, 11, 30, 23);
	ConsoleRenderer::SetCursorPosition(2, 12);
	ConsoleUtil::WriteColored("인벤토리", ConsoleColor::Yellow);

	if (MainPlayer == nullptr || MainPlayer->GetInventory() == nullptr)
	{
		ConsoleRenderer::SetCursorPosition(2, 14);
		ConsoleUtil::WriteColored("골드 : 0G", ConsoleColor::White);
		ConsoleRenderer::SetCursorPosition(2, 16);
		ConsoleUtil::WriteColored("아이템 없음", ConsoleColor::DarkGray);
		return;
	}

	std::shared_ptr<InventoryComponent> Inventory = MainPlayer->GetInventory();

	ConsoleRenderer::SetCursorPosition(2, 14);
	ConsoleUtil::WriteColored("골드 : " + std::to_string(Inventory->GetOwnedGold()) + "G", ConsoleColor::White);

	const std::vector<FInventoryEntry> ItemList = Inventory->GetItemList();
	if (ItemList.empty())
	{
		ConsoleRenderer::SetCursorPosition(2, 16);
		ConsoleUtil::WriteColored("아이템 없음", ConsoleColor::DarkGray);
		return;
	}

	const int MaxVisibleItemCount = 15;
	for (int i = 0; i < static_cast<int>(ItemList.size()) && i < MaxVisibleItemCount; i++)
	{
		const FInventoryEntry& Entry = ItemList[i];
		const ItemData* Data = ItemDataTable::GetInstance().FindItemDataByIndex(Entry.Id);
		const std::string ItemName = Data != nullptr ? Data->Name : "알 수 없는 아이템";

		ConsoleRenderer::SetCursorPosition(2, 16 + i);
		ConsoleUtil::WriteColored(ItemName + " x" + std::to_string(Entry.Amount), ConsoleColor::White);
	}
}

int DrawShopCategorySection(
	const std::vector<const ItemData*>& ShopItems,
	EItemCategory Category,
	const std::string& Title,
	int StartY,
	int& DisplayNumber
)
{
	ConsoleRenderer::SetCursorPosition(34, StartY);
	ConsoleUtil::WriteColored("[" + Title + "]", ConsoleColor::Cyan);

	int Y = StartY + 1;
	for (const ItemData* Data : ShopItems)
	{
		if (Data == nullptr || Data->Category != Category)
		{
			continue;
		}

		ConsoleRenderer::SetCursorPosition(34, Y);
		GInput << DisplayNumber << ". " << Data->Name << " - " << Data->Price << "G";
		DisplayNumber++;
		Y++;
	}

	return Y + 1;
}

void DrawShopListPanel(Player* MainPlayer, const std::vector<const ItemData*>& ShopItems)
{
	ConsoleRenderer::DrawBox(30, 0, 180, 34);

	ConsoleRenderer::SetCursorPosition(116, 2);
	ConsoleUtil::WriteColored("[상점]", ConsoleColor::Yellow);

	ConsoleRenderer::SetCursorPosition(34, 5);
	ConsoleUtil::WriteColored("보유 골드 : " + std::to_string(GetPlayerGold(MainPlayer)) + "G", ConsoleColor::White);

	int DisplayNumber = 1;
	int NextY = DrawShopCategorySection(ShopItems, EItemCategory::Consumable, "소비 아이템", 8, DisplayNumber);
	NextY = DrawShopCategorySection(ShopItems, EItemCategory::Equipment, "장비 아이템", NextY, DisplayNumber);

	if (ShopItems.empty())
	{
		ConsoleRenderer::SetCursorPosition(34, 10);
		ConsoleUtil::WriteColored("판매 중인 상품이 없습니다.", ConsoleColor::DarkGray);
		NextY = 12;
	}

	ConsoleRenderer::SetCursorPosition(34, NextY);
	GInput << "0. 맵으로 돌아가기";
}

void DrawShopDetailPanel(const ItemData* SelectedItem)
{
	ConsoleRenderer::DrawBox(0, 34, 210, 6);

	ConsoleRenderer::SetCursorPosition(2, 35);
	ConsoleUtil::WriteColored("아이템 정보", ConsoleColor::Cyan);

	if (SelectedItem == nullptr)
	{
		ConsoleRenderer::SetCursorPosition(2, 37);
		ConsoleUtil::WriteColored("구매할 아이템 번호를 선택하세요.", ConsoleColor::DarkGray);
		return;
	}

	ConsoleRenderer::SetCursorPosition(2, 36);
	GInput << "이름 : " << SelectedItem->Name;

	ConsoleRenderer::SetCursorPosition(55, 36);
	GInput << "가격 : " << SelectedItem->Price << "G";

	const std::string Description = ShopItemDescriptionBuilder::BuildDescription(SelectedItem);
	ConsoleRenderer::SetCursorPosition(2, 37);
	GInput << Description;

	ConsoleRenderer::SetCursorPosition(2, 38);
	GInput << "1. 구매    0. 뒤로가기";
}
}

void ShopScreen::Draw(
	Player* MainPlayer,
	const std::vector<const ItemData*>& ShopItems,
	const ItemData* SelectedItem,
	const std::string& LastMessage,
	bool bDetailMode
)
{
	ConsoleRenderer::ClearScreen();
	ConsoleUtil::HideCursor();

	GameScreen::DrawCharacterPanel(MainPlayer);
	DrawShopInventoryPanel(MainPlayer);
	DrawShopListPanel(MainPlayer, ShopItems);
	DrawShopDetailPanel(SelectedItem);
	GameScreen::DrawLogPanel(GameInstance::GetInstance().GetLogManager());

	if (!LastMessage.empty())
	{
		ConsoleRenderer::SetCursorPosition(90, 41);
		ConsoleUtil::WriteColored(LastMessage, ConsoleColor::Green);
	}

	ConsoleUtil::ClearArea(2, 48, 205, 1);
	ConsoleRenderer::SetCursorPosition(2, 48);
	GInput << (bDetailMode ? "선택 입력 >> " : "구매할 상품 번호 입력 >> ");
}
