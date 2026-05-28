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
			const std::string Attack = "Modifier_Buff_Attack";
			const std::string Defense = "Modifier_Buff_Defense";
			const std::string ActionSpeed = "Modifier_Buff_ActionSpeed";
		}
		namespace Debuff
		{
			const std::string Poison = "OverTime_Debuff_Poison";
			const std::string Burn = "OverTime_Debuff_Burn";
			const std::string Weakness = "Modifier_Debuff_Weakness";
			const std::string Slow = "Modifier_Debuff_Slow";
		}

		namespace State
		{
			const std::string Stun = "State_Stun";
			const std::string Invincible = "State_Invincible";
		}

		namespace Damage
		{
			const std::string Damage = "Damage";
			const std::string FixedDamage = "Fixed_Damage";
		}
	}	
}
