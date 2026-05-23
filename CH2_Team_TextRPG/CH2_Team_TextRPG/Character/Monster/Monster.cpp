#include "pch.h"
#include "Monster.h"
#include "Data/Character/Stat.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	// Not Implement.
	return false;
}

void Monster::TakeDamage(const DamageContext& Context)
{
	// Not Implement.
}

bool Monster::IsDead() const
{
	// Not Implement.
	return false;
}

int Monster::GetStat(EStatType Type) const
{
	// Not Implement.
	return 0;
}










//Monster::Monster(MonsterSetData&& Desc)
//	: MonsterData(std::move(Desc)),
//	OriginalData(MonsterData)
//{
//}
//
//Monster::~Monster()
//{
//}
//
//bool Monster::Initialize()
//{
//	MonsterData = OriginalData;
//	return Character::Initialize();
//}
//
//void Monster::Attack(Player* player)
//{
//	if (player == nullptr)
//	{
//		return;
//	}
//	player->TakeDamage(MonsterData.Attack);
//}
//
//void Monster::TakeDamage(int Amount)
//{
//	MonsterData.HP -= Amount;
//	if (MonsterData.HP < 0)
//	{
//		MonsterData.HP = 0;
//	}
//}
//
//void Monster::Die()
//{
//	MonsterData.HP = 0;
//}
//
//void Monster::Reset()
//{
//	MonsterData = OriginalData;
//}
//
//void Monster::RestoreHP(int Amount)
//{
//	MonsterData.HP += Amount;
//	if (MonsterData.HP > OriginalData.HP)
//	{
//		MonsterData.HP = OriginalData.HP;
//	}
//}
//
//void Monster::RestoreMP(int Amount)
//{
//}
//
//void Monster::AttackUp(int Amount)
//{
//	MonsterData.Attack += Amount;
//}
//
//void Monster::DefenceUp(int Amount)
//{
//	MonsterData.Defence += Amount;
//}
//
//std::string Monster::GetName() const
//{
//	return MonsterData.Name;
//}
//
//int Monster::GetHP() const
//{
//	return MonsterData.HP;
//}
//
//int Monster::GetMP() const
//{
//	return 0;  
//}
//
//int Monster::GetAttack() const
//{
//	return MonsterData.Attack;
//}
//
//int Monster::GetDefence() const
//{
//	return MonsterData.Defence;
//}
//
//int Monster::GetExp() const
//{
//	return MonsterData.Exp;
//}
//
//std::string Monster::GetDropItemName() const
//{
//	return MonsterData.DropItemName;
//}
//
//int Monster::GetDropItemPrice() const
//{
//	return MonsterData.DropItemPrice;
//}
//
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