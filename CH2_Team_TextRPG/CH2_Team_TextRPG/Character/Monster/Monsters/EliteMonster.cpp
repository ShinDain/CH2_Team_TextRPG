#include "pch.h"
#include "EliteMonster.h"
#include "Character/Player/Player.h"
#include "Data/Character/Damage.h"

EliteMonster::EliteMonster(MonsterSetData&& Desc)
    : Monster(std::move(Desc))
{
        AttackCount = 0;
}
