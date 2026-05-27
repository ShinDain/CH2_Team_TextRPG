#include "pch.h"

#include "EquipmentComponent.h"
#include "Data/Table/ItemDataTable.h"
#include "Enum/EItemType.h"
#include "Item/Item.h"
#include "Effect/Effect.h"
#include "Effect/Factory/EffectFactory.h"
#include "Item/Item_Equipment.h"
#include "Character/Component/InventoryComponent.h"

EquipmentComponent::EquipmentComponent(Object* InOwner) :
	Component(InOwner, "Equipment")
{
}

EquipmentComponent::~EquipmentComponent()
{
}

bool EquipmentComponent::Initialize()
{
	const size_t SlotCount = static_cast<size_t>(EEquipmentType::End);
	EquipmentSlots.reserve(SlotCount);
	for (size_t i = 0; i < SlotCount; ++i)
	{
		EquipmentSlots.emplace(static_cast<EEquipmentType>(i), nullptr);
	}

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

std::unordered_map<EStatType, int> EquipmentComponent::GetEquipmentStats()
{
	std::unordered_map<EStatType, int> retStat;
	retStat[EStatType::Attack] = 0;
	retStat[EStatType::Defense] = 0;
	retStat[EStatType::Health] = 0;
	retStat[EStatType::Mana] = 0;
	retStat[EStatType::ActionSpeed] = 0;

	for (const auto& pair : EquipmentSlots)
	{
		Item_Equipment* equipment = pair.second;
		for (auto& pair : equipment->GetEquipmentStats())
		{
			EStatType type = pair.first;
			int value = pair.second;
			retStat[type] += value;
		}
	}

    return retStat;
}

void EquipmentComponent::OnEquip(Item_Equipment* InEquipment)
{
	if (InEquipment == nullptr)
		return;

	EEquipmentType EquipmentType = InEquipment->GetEquipmentData()->EquipmentType;
	if (EquipmentSlots[EquipmentType] != nullptr)
	{
		OnUnequip(EquipmentType);
	}

	EquipmentSlots[EquipmentType] = InEquipment;
	InEquipment->OnEquip(Owner);
}

const ItemData* EquipmentComponent::OnUnequip(EEquipmentType Type)
{
	std::shared_ptr<InventoryComponent> inventoryComp = Owner->FindComponent<InventoryComponent>("Inventory");
	if (inventoryComp == nullptr)
		return nullptr;

	const ItemData* Ret = nullptr;
	if (EquipmentSlots[Type] != nullptr)
	{
		Item_Equipment* SlotItem = EquipmentSlots[Type];
		Ret = SlotItem->GetItemData();

		SlotItem->OnUnequip(Owner);
		EquipmentSlots[Type] = nullptr;

		inventoryComp->AcquireItem(Ret->Id, 1);
	}

	return Ret;
}
