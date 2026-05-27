#pragma once
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"
#include "Character/Interface/Resource.h"
#include "Character/Interface/Levelable.h"
#include "Character/Interface/UnitStat.h"

class Player : public Character, public IDamageable, public IUnitStat, public IResource, public ILevelable
{
public:
	Player();
	~Player() override;

	bool Initialize() override;
	bool IsDead() const override;
	bool IsMaxLevel() const override;
	
	void ApplyStat(EStatType Type, int Delta) override;
	void AddExp(int Amount) override;

	void TakeDamage(const DamageContext& Context) override;
	void Recovery(EResourceType Type, int Amount) override;
	void Restore(EResourceType Type) override;
	void RestoreAll() override;
	
	int GetStat(EStatType Type) const override;
	int GetLevel() const override;
	int GetExp() const override;

private:
	std::shared_ptr<class StatComponent> Stat;
	std::shared_ptr<class ResourceComponent> Resource;
	std::shared_ptr<class EquipmentComponent> Equip;
	std::shared_ptr<class InventoryComponent> Inventory;
	std::shared_ptr<class LevelComponent> Level;
};
