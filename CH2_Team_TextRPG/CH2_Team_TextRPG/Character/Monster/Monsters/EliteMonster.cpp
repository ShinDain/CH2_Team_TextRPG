#include "pch.h"
#include "EliteMonster.h"
#include "Character/Player/Player.h"
#include "Data/Character/Damage.h"

EliteMonster::EliteMonster(MonsterSetData&& Desc)
    : Monster(std::move(Desc)),
    AttackCount(0)
{
}

void EliteMonster::Attack(Player* player)
{
    if (player == nullptr)
        return;

    AttackCount++;
    if (AttackCount >= 3)
        AttackCount = 0;

    DamageContext etp;
    etp.Attack = MonsterData.Attack;
	etp.SkillMultiplier = (AttackCount == 0) ? 2.f : 1.f; // 3회마다 2배 공격
    etp.AttackCount = 1;
    player->TakeDamage(MonsterData.Attack);
}