#pragma once
#include "Character/Monster/Monster.h"

class BossMonster : public Monster
{
public:
    BossMonster(MonsterSetData&& Desc);
    void Attack(Player* player) override;

private:
    int Phase = 1; // 페이즈
    void UpdatePhase();
};