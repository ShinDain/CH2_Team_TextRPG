#include "pch.h"
#include "BossMonster.h"
#include "Character/Player/Player.h"

BossMonster::BossMonster(MonsterSetData&& Desc)
    : Monster(std::move(Desc)),
    Phase(1)
{
}
void BossMonster::Attack(Player* player)
{
    if (player == nullptr)
        return;

    UpdatePhase();

    DamageContext btp;
    btp.Attack = MonsterData.Attack;
    btp.SkillMultiplier = (Phase == 2) ? 1.5f : 1.f; // 2페이즈면 1.5배
    btp.AttackCount = (Phase == 2) ? 2 : 1;       // 2페이즈면 2회 공격
    player->TakeDamage(btp);
}

void BossMonster::UpdatePhase()
{
    // HP 50% 이하면 2페이즈
    if (MonsterData.HP <= OriginalData.HP / 2)
        Phase = 2;
}