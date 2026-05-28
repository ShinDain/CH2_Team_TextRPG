#pragma once
#include "Character/Monster/Monster.h"

class EliteMonster : public Monster
{
public:
    EliteMonster(MonsterSetData&& Desc);
private:
    int AttackCount = 0; // 공격 횟수 카운트
};