#include "pch.h"
#include "BossMonster.h"
#include "Data/Character/Stat.h"
#include "Character/Component/EffectComponent.h" 
#include <cassert> 

#define COMPONENT_CHECK(x) assert((x) && #x "Component 생성되지 않음")

BossMonster::BossMonster(MonsterSetData&& Desc)
    : Monster(std::move(Desc))
{
    Phase = 1;
}

bool BossMonster::Initialize()
{
    MonsterData.HP *= 2;
    MonsterData.Attack = static_cast<int>(MonsterData.Attack * 1.5f);
    MonsterData.Defense = static_cast<int>(MonsterData.Defense * 1.5f);
    OriginalData = MonsterData;

    if (!Monster::Initialize())
    {
        return false;
    }
    return true;
}

void BossMonster::TakeDamage(int Damage)
{
    Monster::TakeDamage(Damage);
    if (!IsDead())
    {
        UpdatePhase();
    }
}

void BossMonster::UpdatePhase()
{
    int CurrentHP = GetCurrentResource(EResourceType::Health);
    int MaxHP = GetMaxResource(EResourceType::Health);

    if (MaxHP <= 0) return;

    float HPRatio = static_cast<float>(CurrentHP) / MaxHP;

    if (HPRatio <= 0.5f && Phase < 2)
    {
        Phase = 2;
        //COMPONENT_CHECK(Effect);
    }
}