#include "pch.h"
#include "InventoryComponent.h"
#include "Item/Item.h"
#include "Item/Item_Consumable.h"
#include "Item/Item_Equipment.h"
#include "Manager/ItemManager.h"
#include "Character/Component/EquipmentComponent.h"

InventoryComponent::InventoryComponent(Object* InOwner)
	:Component(InOwner, "Inventory")
{
}

InventoryComponent::~InventoryComponent()
{
}

bool InventoryComponent::Initialize()
{
	return true;
}

FInventoryEntry* InventoryComponent::FindInventoryItemEntry(int ItemId)
{
	for (FInventoryEntry& entry : ItemList)
	{
		if (entry.Amount > 0
			&& entry.Id == ItemId
			)
			return &entry;
	}

	return nullptr;
}

bool InventoryComponent::UseItem(int ItemId, std::vector<Object*> Targets)
{
	FInventoryEntry* entry = FindInventoryItemEntry(ItemId);
	if (entry == nullptr)
		return false;

	Item* targetItem = entry->ItemInstance;

	if (targetItem == nullptr)
		return false;

	return UseItem_Implement(targetItem, Targets);
}

bool InventoryComponent::UseItem(const ItemData* ItemData, std::vector<Object*> Targets)
{
	if (ItemData == nullptr)
		return false;

	return UseItem(ItemData->Id, Targets);
}

bool InventoryComponent::UseItem(const Item* ItemInstance, std::vector<Object*> Targets)
{
	if (ItemInstance == nullptr || ItemInstance->GetItemData() == nullptr)
		return false;

	return UseItem(ItemInstance->GetItemData()->Id, Targets);
}

void InventoryComponent::AcquireItem(const std::string ItemName, int Amount)
{
	int itemId = FindItemDataByName(ItemName)->Id;

	AcquireItem(itemId, Amount);
}

void InventoryComponent::AcquireItem(int ItemId, int InAmount)
{
	FInventoryEntry* entry = FindInventoryItemEntry(ItemId);
	if (entry == nullptr)
	{
		AddEntry(ItemId, InAmount);
		return;
	}

	entry->Amount += InAmount;
}

void InventoryComponent::RemoveItem(int ItemId, int InAmount)
{
	FInventoryEntry* entry = FindInventoryItemEntry(ItemId);
	entry->Amount -= InAmount;

	if (entry->Amount <= 0)
	{
		RemoveEntry(entry->Id);
	}
}

void InventoryComponent::Equip(int ItemId)
{
	FInventoryEntry* entry = FindInventoryItemEntry(ItemId);
	if (entry == nullptr)
		return;

	Item* itemInstance = entry->ItemInstance;
	Item_Equipment* equipment = dynamic_cast<Item_Equipment*>(itemInstance);
	if (equipment)
	{
		auto EquipComp = Owner->FindComponent<EquipmentComponent>("Equipment");
		if (EquipComp)
		{
			EquipComp->OnEquip(equipment);
			RemoveItem(ItemId);
		}
	}
}

void InventoryComponent::Equip(const std::string& ItemName)
{
	const ItemData* data = FindItemDataByName(ItemName);
	Equip(data->Id);
}

void InventoryComponent::Unequip(EEquipmentType EquipmentType)
{
	auto EquipComp = Owner->FindComponent<EquipmentComponent>("Equipment");
	if (EquipComp)
	{
		const ItemData* unequipedItemData = EquipComp->OnUnequip(EquipmentType);
		AcquireItem(unequipedItemData->Id, 1);
	}
}

void InventoryComponent::Unequip(int ItemId)
{
	const FEquipmentItemData* equipmentData = EquipmentDataTable::GetInstance().FindEquipmentDataByIndex(ItemId);
	Unequip(equipmentData->EquipmentType);
}

void InventoryComponent::Unequip(const std::string& ItemName)
{
	const ItemData* data = FindItemDataByName(ItemName);
	int itemId = data->Id;
	const FEquipmentItemData* equipmentData = EquipmentDataTable::GetInstance().FindEquipmentDataByIndex(itemId);
	Unequip(equipmentData->EquipmentType);
}

void InventoryComponent::UnequipAll()
{
	for (int i = 0; i < (int)EEquipmentType::End; ++i)
	{
		Unequip((EEquipmentType)i);
	}
}

bool InventoryComponent::UseItem_Implement(Item* ItemInstance, std::vector<Object*> Targets)
{
	if (ItemInstance == nullptr)
		return false;

	const ItemData* Data = ItemInstance->GetItemData();
	if (Data->Category != EItemCategory::Consumable)
		return false;

	FInventoryEntry* targetEntry = FindInventoryItemEntry(Data->Id);
	if (targetEntry)
	{
		targetEntry->ItemInstance->Active(Owner, Targets);
		RemoveItem(targetEntry->Id);
	}

	return true;
}

void InventoryComponent::AddEntry(int ItemId, int Amount)
{
	FInventoryEntry newEntry;
	newEntry.Amount = Amount;
	newEntry.Id = ItemId;
	newEntry.ItemInstance = FindItemById(ItemId);

	if (newEntry.ItemInstance != nullptr)
	{
		ItemList.emplace_back(newEntry);
	}
}

void InventoryComponent::RemoveEntry(int ItemId)
{
	for (FInventoryEntry& entry : ItemList)
	{
		auto it = std::find(ItemList.begin(), ItemList.end(), entry);

		if (it != ItemList.end())
		{
			ItemList.erase(it);
		}
	}
}
