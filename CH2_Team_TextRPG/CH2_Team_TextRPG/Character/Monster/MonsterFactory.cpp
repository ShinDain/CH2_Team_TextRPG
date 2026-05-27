#pragma once
#include "pch.h"
#include "MonsterFactory.h"
#include "Character/Monster/Monsters/BossMonster.h"
#include "Character/Monster/Monsters/EliteMonster.h"
#include "Data/Table/MonsterDataTable.h"

Monster* MonsterFactory::CreateForPlayer(const std::string& Name, Player* player)
{
    const MonsterData* monsterData = FindMonsterDataByName(Name);
    if (monsterData == nullptr)
        return nullptr;

    int Level = player ? player->GetLevel() : 1;

    MonsterSetData data;
    data.Name = monsterData->Name;
    data.HP = monsterData->HP + (rand() % (Level * 10 + 1)) + Level * 20;
    data.Attack = monsterData->Attack + (rand() % (Level * 5 + 1)) + Level * 5;
    data.Defence = monsterData->Defence + (Level * 2);
    data.DropItemName = monsterData->DropItemName;
    data.DropItemPrice = monsterData->DropItemPrice;
    data.Exp = monsterData->Exp;

    Monster* newMonster = nullptr;

    if (monsterData->Type == "Boss")
        newMonster = new BossMonster(std::move(data));
    else if (monsterData->Type == "Elite")
        newMonster = new EliteMonster(std::move(data));
    else
        newMonster = new Monster(std::move(data));

    newMonster->Initialize();
    return newMonster;
}
