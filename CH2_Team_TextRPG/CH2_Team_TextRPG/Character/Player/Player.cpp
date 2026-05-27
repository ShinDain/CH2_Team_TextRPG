#include "pch.h"
#include "Player.h"
#include "Data/Character/Stat.h"
#include "Character/Component/StatComponent.h"
#include "Character/Component/HealthComponent.h"
#include "Character/Component/EquipmentComponent.h"
#include "Character/Component/InventoryComponent.h"
#include "Data/Table/ItemDataTable.h"

Player::Player()
{
	Stat = AddComponent<StatComponent>(this);
	Equip = AddComponent<EquipmentComponent>(this);
	Health = AddComponent<HealthComponent>(this);

	CharacterType = ECharacterType::Player;
	Inventory = AddComponent<InventoryComponent>(this);
}

Player::~Player()
{
	delete Stat;
	Stat = nullptr;
	
	delete Equip;
	Equip = nullptr;
	
	delete Health;
	Health = nullptr;
	
}

bool Player::Initialize()
{
	Stat->Initialize();
	Health->Initialize();
	Equip->Initialize();
	
#if DEBUG_CODE
	Stat->SetStat(EStatType::MaxHP, 200);
	Stat->SetStat(EStatType::Attack, 30);
	Stat->SetStat(EStatType::Defense, 0);
	Stat->SetStat(EStatType::MaxMP, 0);
	Stat->SetStat(EStatType::ActionSpeed, 10);
#endif

	return true;
}

void Player::AcquireItem(int ItemId, int InAmount)
{
	Inventory->AcquireItem(ItemId, InAmount);
}

void Player::AcquireItem(const std::string ItemName, int InAmount)
{
	const ItemData* data = FindItemDataByName(ItemName);
	AcquireItem(data->Id, InAmount);
}

void Player::TakeDamage(const DamageContext& Context)
{
	//Not Implement.	
}

bool Player::IsDead() const
{
	return Health ? Health->IsDead() : false;
}

int Player::GetStat(EStatType Type) const
{
	return Stat ? Stat->GetStat(Type) : INT_MAX;
}

bool Player::CanAfford(int Price)
{
	InventoryComponent* inventoryComp = GetInventory();
	if (inventoryComp)
	{
		return inventoryComp->GetOwnedGold() > Price;
	}

	return false;
}

void Player::ModifyGold(int Value)
{
	InventoryComponent* inventoryComp = GetInventory();
	if (inventoryComp)
	{
		inventoryComp->ModifyGold(Value);
	}
}

InventoryComponent* Player::GetInventory()
{
	return Inventory;
}
