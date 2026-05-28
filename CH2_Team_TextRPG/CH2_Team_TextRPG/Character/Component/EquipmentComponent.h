#pragma once
#include "Core/Component.h"

class Item;
enum class EEquipmentType;
enum class EStatType;
struct ItemData;

class Item_Equipment;
class InventoryComponent;

class EquipmentComponent : public Component
{
	friend InventoryComponent;

public:
	EquipmentComponent(Object* InOwner);
	~EquipmentComponent() override;
	
	bool Initialize() override;

	std::unordered_map<EStatType, int> GetEquipmentStats();

	const std::unordered_map<EEquipmentType, Item_Equipment*> GetEquipmentSlots() { return EquipmentSlots; }
private:
	void OnEquip(Item_Equipment* InEquipment);
	const ItemData* OnUnequip(EEquipmentType Type);

private:
	std::unordered_map<EEquipmentType, Item_Equipment*> EquipmentSlots;
};
