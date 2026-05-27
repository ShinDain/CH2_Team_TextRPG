#include "pch.h"
#include "EquipmentComponent.h"
#include "Item/Item_Equipment.h"
#include "Data/Table/ItemDataTable.h"

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
	EquipmentSlots.reserve(static_cast<size_t>(EEquipmentType::End));
	
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
	retStat[EStatType::MaxHP] = 0;
	retStat[EStatType::MaxMP] = 0;
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

	EEquipmentType equipmentType = InEquipment->GetEquipmentData()->EquipmentType;
	if (EquipmentSlots[equipmentType] != nullptr)
	{
		OnUnequip(equipmentType);
	}

	EquipmentSlots[equipmentType] = InEquipment;
	InEquipment->OnEquip(Owner);
}

const ItemData* EquipmentComponent::OnUnequip(EEquipmentType Type)
{
	const ItemData* retData = nullptr;
	if (EquipmentSlots[Type] != nullptr)
	{
		retData = EquipmentSlots[Type]->GetItemData();

		EquipmentSlots[Type]->OnUnequip(Owner);
		EquipmentSlots[Type] = nullptr;
	}

	return retData;
}
