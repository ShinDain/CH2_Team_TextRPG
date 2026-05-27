#pragma once
#include "Core/Component.h"
#include "Enum/EItemType.h"

struct ItemData;
class Item;

struct FInventoryEntry
{
	int Id;
	int Amount;
	Item* ItemInstance;

	bool operator==(const FInventoryEntry& rhs) const
	{
		return (this->Id == rhs.Id);
	}
};

class InventoryComponent : public Component
{
public:
	InventoryComponent(Object* InOwner);
	virtual ~InventoryComponent() override;

	bool Initialize() override;

	bool UseItem(int ItemId, std::vector<Object*> Targets);
	bool UseItem(const ItemData* ItemData, std::vector<Object*> Targets);
	bool UseItem(const Item* ItemInstance, std::vector<Object*> Targets);

	void AcquireItem(const std::string ItemName, int InAmount = 1);
	void AcquireItem(int ItemId, int InAmount = 1);

	bool RemoveItem(int ItemId, int InAmount = 1);
	void ClearItemList();

	void Equip(int ItemId);
	void Equip(const std::string& ItemName);
	void Unequip(int ItemId);
	void Unequip(const std::string& ItemName);
	void Unequip(EEquipmentType EquipmentType);
	void UnequipAll();

	bool HaveItem(int ItemId);

	void ModifyGold(int Value);

private:
	bool UseItem_Implement(Item* ItemInstance, std::vector<Object*> Targets);

	FInventoryEntry* FindInventoryItemEntry(int ItemId);
	void AddEntry(int ItemId, int Amount);
	void RemoveEntry(int ItemId);

public: 
	const std::vector<FInventoryEntry> GetItemList() const { return ItemList; }
	int GetOwnedGold() const { return OwnedGold; }

private:
	std::vector<FInventoryEntry> ItemList;
	int OwnedGold;
};

