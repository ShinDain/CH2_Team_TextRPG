#include "pch.h"
#include "Item_Equipment.h"
#include "Effect/Effect.h"

Item_Equipment::Item_Equipment(const ItemData* InData, const FEquipmentItemData* InEquipmentData)
	:Item(InData), EquipmentData(InEquipmentData)
{
}

void Item_Equipment::Active(Object* Instigator, std::vector<Object*> Targets)
{
	GLog.AddLog("[Item_Equipment] It's not usable item.");
}

void Item_Equipment::OnEquip(Object* Owner)
{
	for (Effect* effect : Effects)
	{
		effect->Apply(Owner, std::vector<Object*>{Owner});
	}
}

void Item_Equipment::OnUnequip(Object* Owner)
{
	for (Effect* effect : Effects)
	{
		effect->Remove(Owner, std::vector<Object*>{Owner});
	}
}

std::unordered_map<EStatType, int> const Item_Equipment::GetEquipmentStats()
{
	std::unordered_map<EStatType, int> retStats;
	retStats[EStatType::Attack] = 0;
	retStats[EStatType::Defense] = 0;
	retStats[EStatType::Health] = 0;
	retStats[EStatType::Mana] = 0;
	retStats[EStatType::ActionSpeed] = 0;

	for (Effect* effect : Effects)
	{
		if (effect->GetTag() == Game::EffectTag::Stat::Attack)
		{
			retStats[EStatType::Attack] += effect->GetValue();
		}
		else if (effect->GetTag() == Game::EffectTag::Stat::Defense)
		{
			retStats[EStatType::Defense] += effect->GetValue();
		}
		else if (effect->GetTag() == Game::EffectTag::Stat::Health)
		{
			retStats[EStatType::Health] += effect->GetValue();
		}
		else if (effect->GetTag() == Game::EffectTag::Stat::Mana)
		{
			retStats[EStatType::Mana] += effect->GetValue();
		}
		else if (effect->GetTag() == Game::EffectTag::Stat::ActionSpeed)
		{
			retStats[EStatType::ActionSpeed] += effect->GetValue();
		}
	}

	return retStats;
}