#pragma once
#include "Core/Component.h"
#include "Data/Table/ItemDataTable.h"

class Item;

struct FInventoryEntry
{
	int Id;
	int Amount;
	Item* ItemInstance;

	bool operator==(const FInventoryEntry& rhs)
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

	void AcquireItem(const std::string ItemName, int Amount);
	void AcquireItem(int ItemId, int Amount);

	void Equip();
	void Unequip();

	std::vector<FInventoryEntry> GetItemList() { return ItemList; }

private:
	bool UseItem_Implement(Item* ItemInstance, std::vector<Object*> Targets);

	FInventoryEntry* FindInventoryItemEntry(int ItemId);
	void AddEntry(int ItemId, int Amount);
	void RemoveEntry(int ItemId);

private:
	std::vector<FInventoryEntry> ItemList;
};

