#include "pch.h"
#include "Monster.h"
#include "Character/Player/Player.h"

Monster::Monster(MonsterSetData&& Desc)
	: MonsterData(std::move(Desc)),
	OriginalData(MonsterData)
{
	CharacterType = ECharacterType::Monster;
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	MonsterData = OriginalData;
	return Character::Initialize();
}


void Monster::Attack(Player* player)
{
	if (player == nullptr)
	{
		return;
	}
	player->TakeDamage(MonsterData.Attack);
}
void Monster::TakeDamage(int Damage)
{
	MonsterData.HP -= Damage;
	if (MonsterData.HP < 0)
	{
		MonsterData.HP = 0;
	}
}

bool Monster::IsDead() const
{
	return MonsterData.HP <= 0;
}

void Monster::Reset()
{
	MonsterData = OriginalData;
}


std::string Monster::GetName() const
{
	return MonsterData.Name;
}

int Monster::GetHP() const
{
	return MonsterData.HP;
}

int Monster::GetAttack() const
{
	return MonsterData.Attack;
}

int Monster::GetDefence() const
{
	return MonsterData.Defence;
}

int Monster::GetExp() const
{
	return MonsterData.Exp;
}

int Monster::GetDropItemId() const
{
	return MonsterData.DropItemId;
}

int Monster::GetDropGold() const
{
	return MonsterData.DropGold;
}

