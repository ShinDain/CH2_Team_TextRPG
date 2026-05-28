#include "pch.h"
#include "State_Shop.h"
#include "Character/Component/InventoryComponent.h"
#include "Character/Player/Player.h"
#include "Data/Table/ItemDataTable.h"
#include "Enum/EItemType.h"
#include "Manager/InputManager.h"
#include "Manager/StateManager.h"
#include "UI/ConsoleRenderer.h"
#include "UI/ConsoleUtil.h"

#include <random>

namespace
{
constexpr int MaxItemCountPerCategory = 4;

int GetPlayerGold(Player* MainPlayer)
{
	if (MainPlayer == nullptr)
	{
		return 0;
	}

	std::shared_ptr<InventoryComponent> Inventory = MainPlayer->GetInventory();
	return Inventory != nullptr ? Inventory->GetOwnedGold() : 0;
}

void ShuffleItems(std::vector<const ItemData*>& Items)
{
	static std::random_device RandomDevice;
	static std::mt19937 Generator(RandomDevice());

	std::shuffle(Items.begin(), Items.end(), Generator);
}

void AppendRandomItems(
	std::vector<const ItemData*>& OutShopItems,
	std::vector<const ItemData*> CandidateItems,
	int MaxCount
)
{
	ShuffleItems(CandidateItems);

	const int CandidateCount = static_cast<int>(CandidateItems.size());
	const int SelectCount = CandidateCount < MaxCount ? CandidateCount : MaxCount;
	for (int i = 0; i < SelectCount; i++)
	{
		OutShopItems.push_back(CandidateItems[i]);
	}
}

std::vector<const ItemData*> BuildShopItems()
{
	std::vector<const ItemData*> ConsumableItems;
	std::vector<const ItemData*> EquipmentItems;

	const std::vector<const ItemData*> ItemDatas = ItemDataTable::GetInstance().GetItemDatas();
	for (const ItemData* Data : ItemDatas)
	{
		if (Data == nullptr)
		{
			continue;
		}

		if (Data->Category == EItemCategory::Consumable)
		{
			ConsumableItems.push_back(Data);
		}
		else if (Data->Category == EItemCategory::Equipment)
		{
			EquipmentItems.push_back(Data);
		}
	}

	std::vector<const ItemData*> ShopItems;
	AppendRandomItems(ShopItems, ConsumableItems, MaxItemCountPerCategory);
	AppendRandomItems(ShopItems, EquipmentItems, MaxItemCountPerCategory);
	return ShopItems;
}

int DrawShopCategorySection(
	const std::vector<const ItemData*>& ShopItems,
	EItemCategory Category,
	const std::string& Title,
	int StartY,
	int& DisplayNumber
)
{
	ConsoleRenderer::SetCursorPosition(68, StartY);
	ConsoleUtil::WriteColored("[" + Title + "]", ConsoleColor::Cyan);

	int Y = StartY + 1;
	for (const ItemData* Data : ShopItems)
	{
		if (Data == nullptr || Data->Category != Category)
		{
			continue;
		}

		ConsoleRenderer::SetCursorPosition(68, Y);
		GInput << DisplayNumber << ". " << Data->Name << " - " << Data->Price << "G";
		DisplayNumber++;
		Y++;
	}

	return Y + 1;
}

void DrawShopScreen(Player* MainPlayer, const std::vector<const ItemData*>& ShopItems, const std::string& LastMessage)
{
	ConsoleRenderer::ClearScreen();
	ConsoleUtil::HideCursor();

	ConsoleRenderer::DrawBox(55, 6, 100, 40);
	ConsoleRenderer::SetCursorPosition(96, 9);
	ConsoleUtil::WriteColored("상점", ConsoleColor::Yellow);

	ConsoleRenderer::SetCursorPosition(68, 12);
	ConsoleUtil::WriteColored("보유 골드 : " + std::to_string(GetPlayerGold(MainPlayer)) + "G", ConsoleColor::White);

	int DisplayNumber = 1;
	int NextY = DrawShopCategorySection(ShopItems, EItemCategory::Consumable, "소비 아이템", 15, DisplayNumber);
	NextY = DrawShopCategorySection(ShopItems, EItemCategory::Equipment, "장비 아이템", NextY, DisplayNumber);

	if (ShopItems.empty())
	{
		ConsoleRenderer::SetCursorPosition(68, 17);
		ConsoleUtil::WriteColored("판매 중인 상품이 없습니다.", ConsoleColor::DarkGray);
		NextY = 19;
	}

	ConsoleRenderer::SetCursorPosition(68, NextY);
	GInput << "0. 맵으로 돌아가기";

	if (!LastMessage.empty())
	{
		ConsoleRenderer::SetCursorPosition(68, 36);
		ConsoleUtil::WriteColored(LastMessage, ConsoleColor::Green);
	}

	ConsoleRenderer::SetCursorPosition(68, 41);
	GInput << "구매할 상품 번호 입력 >> ";
}

std::string TryBuyItem(Player* MainPlayer, const std::vector<const ItemData*>& ShopItems, int Input)
{
	if (Input < 1 || Input > static_cast<int>(ShopItems.size()))
	{
		return "잘못된 상품 번호입니다.";
	}

	if (MainPlayer == nullptr)
	{
		return "플레이어 정보를 찾을 수 없습니다.";
	}

	const ItemData* Data = ShopItems[Input - 1];
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
}

State_Shop::State_Shop()
{
	Name = "Shop";
}

void State_Shop::Enter()
{
	ShopItems = BuildShopItems();
	LastMessage.clear();
	GLog.AddLog("상점에 입장했습니다.");
}

void State_Shop::Process()
{
	Player* MainPlayer = GameInstance::GetInstance().GetMainPlayer();

	DrawShopScreen(MainPlayer, ShopItems, LastMessage);

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

	LastMessage = TryBuyItem(MainPlayer, ShopItems, Input);
}

void State_Shop::Exit()
{
	ShopItems.clear();
	LastMessage.clear();
	GLog.AddLog("상점을 떠났습니다.");
}
