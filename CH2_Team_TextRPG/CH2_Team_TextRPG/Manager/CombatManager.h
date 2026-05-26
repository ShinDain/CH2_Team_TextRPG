#pragma once
#include <vector>
#include "Core/Object.h"
#include "Effect/Effect.h"
#include "Data/Table/SkillDataTable.h"

class CombatManager
{
public:
	static void ExecuteBasicAttack(Object* Attacker, Object* Defender);
	static void ApplyEffects(Object* Caster, const std::vector<Object*>& Targets, const std::vector<Effect>& Effects);

};
