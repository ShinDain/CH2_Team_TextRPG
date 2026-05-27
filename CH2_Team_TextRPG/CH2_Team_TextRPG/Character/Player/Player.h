#pragma once
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"
#include "Character/Interface/Resource.h"
#include "Character/Interface/Levelable.h"
#include "Character/Interface/UnitStat.h"
#include "Character/Interface/Trade.h"

class Player : public Character, public IDamageable, public IUnitStat, public IResource, public ILevelable, public ITrade
{
public:
	Player();
	~Player() override;

	bool Initialize() override;
	bool IsMaxLevel() const override;
	
	void ApplyStat(EStatType Type, int Delta) override;
	void AddExp(int Amount) override;

	void AcquireItem(int ItemId, int InAmount = 1);
	void AcquireItem(const std::string ItemName, int InAmount = 1);

	// IDamageable's interface
public:
	void TakeDamage(const DamageContext& Context) override;
	void Recovery(EResourceType Type, int Amount) override;
	void Restore(EResourceType Type) override;
	void RestoreAll() override;
	
	bool IsDead() const override;

	// IUnitStat's interface
public:
	int GetStat(EStatType Type) const override;
	int GetLevel() const override;
	int GetExp() const override;

	// ITrade's Interface
public:
	virtual bool CanAfford(int Price) override;
	virtual void ModifyGold(int Value) override;

	virtual std::shared_ptr<class InventoryComponent> GetInventory() override;
	
private:
	std::shared_ptr<class StatComponent> Stat;
	std::shared_ptr<class ResourceComponent> Resource;
	std::shared_ptr<class EquipmentComponent> Equip;
	std::shared_ptr<class InventoryComponent> Inventory;
	std::shared_ptr<class LevelComponent> Level;
};
