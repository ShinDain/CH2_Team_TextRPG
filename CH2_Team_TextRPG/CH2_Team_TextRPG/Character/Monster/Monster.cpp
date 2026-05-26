#include "pch.h"
#include "Monster.h"
#include "Character/Player/Player.h"
#include "Data/Character/Stat.h"

int Monster::GetStat(EStatType Type) const
{
	// Not Implement.
	return 0;
}

Monster::Monster(MonsterSetData&& Desc)
	: MonsterData(std::move(Desc)),
	OriginalData(MonsterData)
{
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
	//if (player == nullptr)
	//{
	//	return;
	//}
	//// 몬스터 공격을 DamageContext로 포장하여 전달
	//DamageContext ctx;
	//ctx.Attack = MonsterData.Attack;
	//ctx.SkillMultiplier = 1.f;
	//ctx.AttackCount = 1;

	//player->TakeDamage(ctx);
}
void Monster::TakeDamage(const DamageContext& Context)
{
	/*int damage = std::max(0, Context.Attack - MonsterData.Defence);
	MonsterData.HP -= damage;
	if (MonsterData.HP < 0)
	{
		MonsterData.HP = 0;
	}*/
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

int Monster::GetMP() const
{
	return 0;  
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

//MonsterSetData GenerateStat(Player* player)
//{
//	int MinHP = player->Level * 20;
//	int MaxHP = player->Level * 30;
//	int MinAttack = player->Level * 5;
//	int MaxAttack = player->Level * 10;
//
//	int RandomHP = MinHP + (rand() % (MaxHP - MinHP + 1));
//	int RandomAttack = MinAttack + (rand() % (MaxAttack - MinAttack + 1));
//
//	return MonsterSetData(
//		"Slime",
//		"Jelly",
//		RandomHP,
//		RandomAttack,
//		2,
//		10,
//		Level * 10
//	);
//}