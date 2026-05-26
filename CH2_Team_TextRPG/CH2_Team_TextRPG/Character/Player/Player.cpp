#include "pch.h"
#include "Player.h"
#include "Data/Character/Stat.h"
#include "Character/Component/StatComponent.h"
#include "Character/Component/HealthComponent.h"
#include "Character/Component/EquipmentComponent.h"
#include "Character/Component/InventoryComponent.h"

Player::Player()
{
	Stat = AddComponent<StatComponent>(this);
	Equip = AddComponent<EquipmentComponent>(this);
	Health = AddComponent<HealthComponent>(this);
	Inventory = AddComponent<InventoryComponent>(this);
}

Player::~Player()
{
}

bool Player::Initialize()
{
	// Not Implement.
	return false;
}

void Player::TakeDamage(const DamageContext& Context)
{
	// Not Implement.
}

bool Player::IsDead() const
{
	// Not Implement.
	return false;
}

int Player::GetStat(EStatType Type) const
{
	// Not Implement.
	return 0;
}
