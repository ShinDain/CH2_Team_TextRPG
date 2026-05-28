#include "pch.h"
#include "ShopItemDescriptionBuilder.h"
#include "Data/Table/ItemDataTable.h"
#include "Effect/EffectData.h"
#include "Enum/EItemType.h"
#include "Item/ItemData.h"

namespace
{
std::string FormatSignedValue(int Value)
{
	return Value >= 0 ? "+" + std::to_string(Value) : std::to_string(Value);
}

std::string BuildSingleEffectDescription(const EffectData& Effect)
{
	if (Effect.Tag == "Resource_RecoveryHeal")
	{
		return "HP 회복 " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Resource_RecoveryMana")
	{
		return "Mana 회복 " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Buff_Attack" || Effect.Tag == "Stat_Attack")
	{
		return "Attack " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Buff_Defense" || Effect.Tag == "Stat_Defense")
	{
		return "Defense " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Buff_ActionSpeed" || Effect.Tag == "Stat_ActionSpeed")
	{
		return "ActionSpeed " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Stat_Health")
	{
		return "HP " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Stat_Mana")
	{
		return "Mana " + FormatSignedValue(Effect.Value);
	}
	if (Effect.Tag == "Damage")
	{
		return "효과 : Damage " + std::to_string(Effect.Value);
	}
	if (Effect.Tag == "CC_Stun")
	{
		return std::to_string(Effect.Value) + "턴 동안 기절";
	}
	if (Effect.Tag == "Buff_Invincible")
	{
		return std::to_string(Effect.Value) + "턴 동안 무적";
	}

	return "효과 : " + Effect.Tag + " " + std::to_string(Effect.Value);
}

std::string BuildEffectListDescription(const std::vector<EffectData>& EffectDatas, uint32_t Duration)
{
	if (EffectDatas.empty())
	{
		return "효과 정보가 없습니다.";
	}

	std::string Description;
	for (int i = 0; i < static_cast<int>(EffectDatas.size()); i++)
	{
		if (!Description.empty())
		{
			Description += " / ";
		}
		Description += BuildSingleEffectDescription(EffectDatas[i]);
	}

	if (Duration > 0)
	{
		Description += " / " + std::to_string(Duration) + "턴 동안 효과 지속";
	}

	return Description;
}
}

std::string ShopItemDescriptionBuilder::BuildDescription(const ItemData* Item)
{
	if (Item == nullptr)
	{
		return "아이템 정보를 찾을 수 없습니다.";
	}

	if (Item->Category == EItemCategory::Consumable)
	{
		const FConsumableItemData* ConsumableData =
			ConsumableDataTable::GetInstance().FindConsumableDataByIndex(Item->Id);
		if (ConsumableData == nullptr)
		{
			return "상세 효과 정보가 없습니다.";
		}

		return BuildEffectListDescription(ConsumableData->EffectDatas, ConsumableData->Duration);
	}

	if (Item->Category == EItemCategory::Equipment)
	{
		const FEquipmentItemData* EquipmentData =
			EquipmentDataTable::GetInstance().FindEquipmentDataByIndex(Item->Id);
		if (EquipmentData == nullptr)
		{
			return "상세 효과 정보가 없습니다.";
		}

		return BuildEffectListDescription(EquipmentData->EffectDatas, 0);
	}

	return "상세 효과 정보가 없습니다.";
}
