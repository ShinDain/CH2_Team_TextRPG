#include "pch.h"
#include "Player.h"
#include "Data/Character/Stat.h"
#include "Data/Character/Damage.h"
#include "Character/Component/StatComponent.h"
#include "Character/Component/ResourceComponent.h"
#include "Character/Component/EquipmentComponent.h"
#include "Character/Component/InventoryComponent.h"
#include "Character/Component/LevelComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Data/Table/ItemDataTable.h"

#define COMPONENT_CHECK(x) assert((x) && #x "Component 생성되지 않음")

Player::Player()
{
	Name = "Player";
	CharacterType = ECharacterType::Player;
	
	Stat = AddComponent<StatComponent>(this);
	Equip = AddComponent<EquipmentComponent>(this);
	Resource = AddComponent<ResourceComponent>(this);
	Inventory = AddComponent<InventoryComponent>(this);
	Level = AddComponent<LevelComponent>(this);
	Skill = AddComponent<SkillComponent>(this);
}

Player::~Player()
{
		
}

bool Player::Initialize()
{
	Stat->Initialize();

#if DEBUG_CODE
	Stat->SetStat(EStatType::Health, 200);
	Stat->SetStat(EStatType::Attack, 30);
	Stat->SetStat(EStatType::Defense, 0);
	Stat->SetStat(EStatType::Mana, 100);
	Stat->SetStat(EStatType::ActionSpeed, 10);
#endif

	Resource->Initialize();
	Equip->Initialize();
	Inventory->Initialize();
	Level->Initialize();
	Skill->Initialize();

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

void Player::TakeDamage(int Damage)
{
	Resource->Decrease(EResourceType::Health, Damage);
}

void Player::Recovery(EResourceType Type, int Amount)
{
	COMPONENT_CHECK(Resource);
	Resource->Increase(Type, Amount);
}

void Player::Restore(EResourceType Type)
{
	COMPONENT_CHECK(Resource);
	Resource->Restore(Type);
}

void Player::RestoreAll()
{
	COMPONENT_CHECK(Resource);
	Resource->Restore();
}

bool Player::IsDead() const
{
	COMPONENT_CHECK(Resource);
	return Resource->GetCurrent(EResourceType::Health) <= 0;
}

bool Player::IsMaxLevel() const
{
	COMPONENT_CHECK(Level);
	return Level->IsMaxLevel();
}

int Player::GetStat(EStatType Type) const
{
	COMPONENT_CHECK(Stat);
	return Stat->GetStat(Type);
}

int Player::GetLevel() const
{
	COMPONENT_CHECK(Level);
	return Level->GetLevel();
}

int Player::GetExp() const
{
	COMPONENT_CHECK(Level);
	return Level->GetExp();
}

int Player::GetCurrentResource(EResourceType Type) const
{
	COMPONENT_CHECK(Resource);
	return Resource->GetCurrent(Type);
}

int Player::GetMaxResource(EResourceType Type) const
{
	COMPONENT_CHECK(Resource);
	return Resource->GetMax(Type);
}

void Player::ApplyStat(EStatType Type, int Delta)
{
	if (Delta == 0)
	{
		return;
	}
	
	if (IsResourceType(Type))
	{
		COMPONENT_CHECK(Resource);
		const EResourceType ResourceType = ToResourceType(Type);
		if (Delta > 0)
		{
			Resource->Increase(ResourceType, Delta);
		}
		else
		{
			Resource->Decrease(ResourceType, -Delta);
		}
	}
	else
	{
		COMPONENT_CHECK(Stat);
		Stat->AddStat(Type, Delta);
	}
}

void Player::SetBaseStat(EStatType Type, int Value)
{
	COMPONENT_CHECK(Stat);
	Stat->SetStat(Type, Value);
}

void Player::AddExp(int Amount)
{
	COMPONENT_CHECK(Level);
	Level->AddExp(Amount);
}

bool Player::CanAfford(int Price)
{
	std::shared_ptr<InventoryComponent> inventoryComp = GetInventory();
	if (inventoryComp)
	{
		return inventoryComp->GetOwnedGold() >= Price;
	}

	return false;
}

void Player::ModifyGold(int Value)
{
	std::shared_ptr<InventoryComponent> inventoryComp = GetInventory();
	if (inventoryComp)
	{
		inventoryComp->ModifyGold(Value);
	}
}

std::shared_ptr<InventoryComponent> Player::GetInventory()
{
	return Inventory;
}

std::shared_ptr<InventoryComponent> Player::GetInventory() const
{
	return Inventory;
}
