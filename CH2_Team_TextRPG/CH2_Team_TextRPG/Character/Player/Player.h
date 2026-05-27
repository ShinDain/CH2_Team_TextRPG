#pragma once
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"
#include "Character/Interface/UnitStat.h"
#include "Character/Interface/Trade.h"

class Player : public Character, public IDamageable, public IUnitStat, public ITrade
{
public:
	Player();
	~Player() override;
	
	bool Initialize() override;

	void AcquireItem(int ItemId, int InAmount = 1);
	void AcquireItem(const std::string ItemName, int InAmount = 1);

	// IDamageable's interface
public:
	void TakeDamage(const DamageContext& Context) override;
	bool IsDead() const override;

	// IUnitStat's interface
public:
	int GetStat(EStatType Type) const override;
	
	// ITrade's Interface
public:
	virtual bool CanAfford(int Price) override;
	virtual void ModifyGold(int Value) override;

	virtual InventoryComponent* GetInventory() override;
	
private:
	class StatComponent* Stat;
	class HealthComponent* Health;
	class EquipmentComponent* Equip;
	class InventoryComponent* Inventory;
	
};
