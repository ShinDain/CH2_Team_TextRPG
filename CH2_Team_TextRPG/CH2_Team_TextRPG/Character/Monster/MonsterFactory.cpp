#include "pch.h"
#include "MonsterFactory.h"
#include "Character/Monster/Monsters/BossMonster.h"
#include "Character/Monster/Monsters/EliteMonster.h"
#include "Character/Player/Player.h"
#include "Data/Table/MonsterDataTable.h"
#include "Manager/ObjectManager.h"
#include "Data/Character/Stat.h"

Monster* MonsterFactory::CreateForPlayer(const std::string& Name, Player* player)
{
    const MonsterData* monsterData = FindMonsterDataByName(Name);
    if (monsterData == nullptr)
    {
        return nullptr;
    }

    int Level = player ? player->GetLevel() : 1;

    MonsterSetData data;
    data.Name = monsterData->Name;
    data.HP = monsterData->HP;
    data.Attack = monsterData->Attack;
    data.Defense = monsterData->Defense;
	data.ActionSpeed = monsterData->ActionSpeed;
    data.DropItemId = monsterData->DropItemId;
    data.DropGold = monsterData->DropGold;
    data.Exp = monsterData->Exp;

    Monster* newMonster = nullptr;

    if (monsterData->Type == "Boss")
        newMonster = new BossMonster(std::move(data));
    else if (monsterData->Type == "Elite")
        newMonster = new EliteMonster(std::move(data));
    else
        newMonster = new Monster(std::move(data));

    newMonster->Initialize();

    int hpBonus = (rand() % (Level * 10 + 1)) + Level * 20;
    int attackBonus = (rand() % (Level * 5 + 1)) + Level * 5;
    int defenseBonus = Level * 2;

    newMonster->ApplyStat(EStatType::Health, hpBonus);
    newMonster->ApplyStat(EStatType::Attack, attackBonus);
    newMonster->ApplyStat(EStatType::Defense, defenseBonus);

    ObjectManager::GetInstance().AddObject(newMonster);

    return newMonster;
}
