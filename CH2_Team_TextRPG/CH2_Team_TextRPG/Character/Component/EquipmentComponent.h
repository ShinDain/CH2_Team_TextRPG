#pragma once
#include "Core/Component.h"
#include "Enum/EItemType.h"

class Item;
enum class EEquipmentType;
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

private:
	void OnEquip(Item_Equipment* InEquipment);
	const ItemData* OnUnequip(EEquipmentType Type);

private:
	std::unordered_map<EEquipmentType, Item_Equipment*> EquipmentSlots;
};
