#pragma once
#include "Core/Component.h"

class Item;
enum class EEquipmentType;
class EquipmentComponent : public Component
{
public:
	EquipmentComponent(Object* InOwner);
	~EquipmentComponent() override;
	
	bool Initialize() override;
	
	bool Equip(Item* InItem);
	void Unequip(EEquipmentType Slot);
	void UnequipAll();

	void ApplySlotItem(const Item& InItem);
	
	Item* FindItemFromSlot(EEquipmentType Slot);
	
private:
	std::unordered_map<EEquipmentType, Item*> Slots;
};
