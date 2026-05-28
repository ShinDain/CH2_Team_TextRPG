#include "pch.h"
#include "EliteMonster.h"

EliteMonster::EliteMonster(MonsterSetData&& Desc)
    : Monster(std::move(Desc))
{
        AttackCount = 0;
}
