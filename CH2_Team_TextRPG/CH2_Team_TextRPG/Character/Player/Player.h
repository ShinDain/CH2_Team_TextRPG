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
	void SetBaseStat(EStatType Type, int Value);
	void AddExp(int Amount) override;

	void AcquireItem(int ItemId, int InAmount = 1);
	void AcquireItem(const std::string ItemName, int InAmount = 1);

public:
	void TakeDamage(int Damage) override;
	void Recovery(EResourceType Type, int Amount) override;
	void Restore(EResourceType Type) override;
	void RestoreAll() override;
	
	bool IsDead() const override;

public:
	int GetStat(EStatType Type) const override;
	int GetLevel() const override;
	int GetExp() const override;
	int GetCurrentResource(EResourceType Type) const override;
	int GetMaxResource(EResourceType Type) const override;

public:
	virtual bool CanAfford(int Price) override;
	virtual void ModifyGold(int Value) override;

	virtual std::shared_ptr<class InventoryComponent> GetInventory() override;
	std::shared_ptr<class InventoryComponent> GetInventory() const;
	
private:
	std::shared_ptr<class StatComponent> Stat;
	std::shared_ptr<class ResourceComponent> Resource;
	std::shared_ptr<class EquipmentComponent> Equip;
	std::shared_ptr<class InventoryComponent> Inventory;
	std::shared_ptr<class LevelComponent> Level;
};
