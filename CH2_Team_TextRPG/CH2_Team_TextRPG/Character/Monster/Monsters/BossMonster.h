#pragma once
#include "Character/Monster/Monster.h"

class BossMonster : public Monster
{
public:
    BossMonster(MonsterSetData&& Desc);
	bool Initialize() override;
    void TakeDamage(int Damage);
private:
    int Phase = 1; // 페이즈
    void UpdatePhase();
};