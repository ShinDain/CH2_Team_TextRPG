#include "pch.h"
#include "CombatManager.h"
#include "Character/Component/StatComponent.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"


void CombatManager::ExecuteBasicAttack(Object* Attacker, Object* Defender)
{
	if (!Attacker || !Defender) return;

	IUnitStat* AttackerStat = dynamic_cast<IUnitStat*>(Attacker);
    IUnitStat* DefenderStat = dynamic_cast<IUnitStat*>(Defender);
    int atk = AttackerStat->GetStat(EStatType::Attack);
    int def = DefenderStat->GetStat(EStatType::Defense);
	int Damage = atk / def;
	GInput << "[시스템] " << Attacker->GetName() << "의 일반 공격! " << Defender->GetName() << "에게 " << Damage << "의 데미지!\n";
	// Defender->TakeDamage(Damage);
}

void CombatManager::ApplyEffects(Object* Caster, const std::vector<Object*>& Targets, const std::vector<Effect>& Effects)
{
	for (Object* Target : Targets)
	{
		if (!Target) continue;

		for (const Effect& Effect : Effects)
		{
			
		}
	}
}