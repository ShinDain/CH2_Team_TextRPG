#include "pch.h"
#include "EquipmentComponent.h"

#include "StatComponent.h"
#include "Data/Table/ItemDataTable.h"
#include "Enum/EItemType.h"
#include "Item/Item.h"
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"



EquipmentComponent::EquipmentComponent(Object* InOwner) :
	Component(InOwner, "Equipment")
{
}

EquipmentComponent::~EquipmentComponent()
{
}

bool EquipmentComponent::Initialize()
{
	Slots.reserve(static_cast<size_t>(EEquipmentType::End));
	
#if DEBUG_CODE
	EffectData D = EffectData();
	D.Tag = "Heal";
	D.Value = 30;
	Effect* NewEffect = EffectFactory::CreateEffect(D);
	if (!NewEffect) 
		return false;
	
	NewEffect->Apply(Owner, {});
	delete NewEffect;
#endif
	
	return true;
}

bool EquipmentComponent::Equip(Item* InItem)
{
	if (!InItem) return false;

	const ItemData* ItemData = InItem->GetItemData();
	bool ItemValidate = !ItemData || ItemData->Category != EItemCategory::Equipment; 
	if (ItemValidate)
	{
		return false;
	}

	const FEquipmentItemData* EquipData = EquipmentDataTable::GetInstance().FindEquipmentDataByIndex(ItemData->Id);
	if (!EquipData)
	{
		return false;
	}

	const EEquipmentType Slot = EquipData->EquipmentType;
	if (auto It = Slots.find(Slot); It != Slots.end() && It->second != nullptr)
	{
		Unequip(Slot);
	}

	for (const auto& EffectData : EquipData->EffectDatas)
	{
		Effect* NewEffect = EffectFactory::CreateEffect(EffectData);
		if (!NewEffect) continue;
		NewEffect->Apply(Owner, {});
		delete NewEffect;
	}

	Slots[Slot] = InItem;

	return true;
}

void EquipmentComponent::Unequip(EEquipmentType Slot)
{
	auto It = Slots.find(Slot);
	if (It == Slots.end() || It->second == nullptr)
	{
		return;
	}

	Item* SlotItem = It->second;

	const ItemData* ItemData = SlotItem->GetItemData();
	if (ItemData)
	{
		const FEquipmentItemData* EquipData = EquipmentDataTable::GetInstance().FindEquipmentDataByIndex(ItemData->Id);
		if (!EquipData)
		{
			return;
		}
		
		for (const auto& EffData : EquipData->EffectDatas)
		{
			Effect* NewEffect = EffectFactory::CreateEffect(EffData);
			if (!NewEffect) continue;
			NewEffect->Remove(Owner, {});
			delete NewEffect;
			NewEffect = nullptr;
		}
	}
	Slots.erase(It);
}

void EquipmentComponent::UnequipAll()
{
	std::vector<EEquipmentType> AllSlots;
	AllSlots.reserve(Slots.size());
	for (const auto& Pair : Slots)
	{
		AllSlots.push_back(Pair.first);
	}
	for (EEquipmentType Slot : AllSlots)
	{
		Unequip(Slot);
	}
}

Item* EquipmentComponent::FindItemFromSlot(EEquipmentType Slot)
{
	auto It = Slots.find(Slot);
	if (It != Slots.end())
	{
		return It->second;
	}
	return nullptr;
}
