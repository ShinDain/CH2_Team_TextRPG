#pragma once

namespace Game
{
	namespace EffectTag
	{
		namespace Stat
		{
			const std::string Attack = "Stat_Attack";
			const std::string Defense = "Stat_Defense";
			const std::string Health = "Stat_Health";
			const std::string Mana = "Stat_Mana";
			const std::string ActionSpeed = "Stat_ActionSpeed";	
		}
		namespace Resource
		{
			const std::string RestoreHeal = "Resource_RestoreHeal";
			const std::string RestoreMana = "Resource_RestoreMana";
			const std::string RecoveryHeal = "Resource_RecoveryHeal";
			const std::string RecoveryMana = "Resource_RecoveryMana";
		}

		namespace Buff
		{
			const std::string Attack = "Buff_Attack";
			const std::string Defense = "Buff_Defense";
			const std::string ActionSpeed = "Buff_ActionSpeed";

			const std::string Invincible = "Buff_Invincible";
		}
		namespace Debuff
		{
			const std::string Poison = "Debuff_Poison";
			const std::string Burn = "Debuff_Burn";
			const std::string Freeze = "Debuff_Freeze";
		}

		namespace CC
		{
			const std::string Stun = "CC_Stun";
		}

		const std::string EFFECT_TAG_DAMAGE = "Damage";
	}	
}
