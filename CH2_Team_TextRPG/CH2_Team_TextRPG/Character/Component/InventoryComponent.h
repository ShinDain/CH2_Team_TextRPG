#pragma once
#include "Core/Component.h"
#include "Data/Table/ItemDataTable.h"

struct InventoryEntry
{
	int Id;
	int Amount;
	std::string Name;
};

class InventoryComponent : public Component
{
public:
	InventoryComponent(Object* InOwner);
	virtual ~InventoryComponent() override;

	bool Initialize() override;
	
	bool UseItem();

	void AcqireItem(const std::string ItemName);
	std::vector<const std::string&> GetItemList();

private:
	std::vector<InventoryEntry> Entries;
	std::unordered_map<std::string, InventoryEntry&> NameMap;
	std::unordered_map<int, InventoryEntry&> IdMap;
};

