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
	// 몬스터 공격을 DamageContext로 포장하여 전달
	DamageContext mtp;
	mtp.Attack = MonsterData.Attack;

	player->TakeDamage(mtp);
}
void Monster::TakeDamage(const DamageContext& Context)
{
	int damage = std::max(0, Context.Attack - MonsterData.Defence);
	MonsterData.HP -= damage;
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

std::string Monster::GetDropItemName() const
{
	return MonsterData.DropItemName;
}

int Monster::GetDropItemPrice() const
{
	return MonsterData.DropItemPrice;
}

