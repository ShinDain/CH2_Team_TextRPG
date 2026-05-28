#include "pch.h"
#include "Monster.h"
#include "Data/Character/Stat.h"
#include "Character/Player/Player.h"
#include "Character/Component/StatComponent.h"
#include "Character/Component/ResourceComponent.h"
#include "Character/Component/EffectComponent.h"
#include "Character/Component/SkillComponent.h"

#define COMPONENT_CHECK(x) assert((x) && #x "Component 생성되지 않음")

Monster::Monster(MonsterSetData&& Desc)
	: MonsterData(std::move(Desc)),
	OriginalData(MonsterData)
{
	Name = MonsterData.Name;
	CharacterType = ECharacterType::Monster;

	Stat = AddComponent<StatComponent>(this);
	Resource = AddComponent<ResourceComponent>(this);
	Effect = AddComponent<EffectComponent>(this);
	Skill = AddComponent<SkillComponent>(this);
}

Monster::~Monster()
{
}

bool Monster::Initialize()
{
	COMPONENT_CHECK(Stat);
	COMPONENT_CHECK(Resource);
	COMPONENT_CHECK(Effect);
	COMPONENT_CHECK(Skill);

	Stat->Initialize();

	Stat->SetStat(EStatType::Health, MonsterData.HP);
	Stat->SetStat(EStatType::Attack, MonsterData.Attack);
	Stat->SetStat(EStatType::Defense, MonsterData.Defense);
	Stat->SetStat(EStatType::ActionSpeed, MonsterData.ActionSpeed);

	Resource->Initialize();
	Effect->Initialize();
	Skill->Initialize();

	return true;
}

void Monster::TakeDamage(int Damage)
{
	COMPONENT_CHECK(Resource);
	Resource->Decrease(EResourceType::Health, Damage);
}

bool Monster::IsDead() const
{
	COMPONENT_CHECK(Resource);
	return Resource->GetCurrent(EResourceType::Health) <= 0;
}

void Monster::Decrease(EResourceType Type, int Amount)
{
	COMPONENT_CHECK(Resource);
	Resource->Decrease(Type, Amount);
}

void Monster::Recovery(EResourceType Type, int Amount)
{
	COMPONENT_CHECK(Resource);
	Resource->Increase(Type, Amount);
}

void Monster::Restore(EResourceType Type)
{
	COMPONENT_CHECK(Resource);
	Resource->Restore(Type);
}

void Monster::RestoreAll()
{
	COMPONENT_CHECK(Resource);
	Resource->Restore();
}

void Monster::ApplyStat(EStatType Type, int Delta)
{
	if (Delta == 0) return;

	if (IsResourceType(Type))
	{
		COMPONENT_CHECK(Stat);
		Stat->AddStat(Type, Delta);

		COMPONENT_CHECK(Resource);
		const EResourceType ResourceType = ToResourceType(Type);
		if (Delta > 0)
		{
			Resource->Increase(ResourceType, Delta);
		}
		else
		{
			Resource->Decrease(ResourceType, -Delta);
		}
	}
	else
	{
		COMPONENT_CHECK(Stat);
		Stat->AddStat(Type, Delta);
	}
}

void Monster::SetBaseStat(EStatType Type, int Value)
{
	COMPONENT_CHECK(Stat);
	Stat->SetStat(Type, Value);
}

int Monster::GetStat(EStatType Type) const
{
	COMPONENT_CHECK(Stat);
	return Stat->GetStat(Type);
}

int Monster::GetCurrentResource(EResourceType Type) const
{
	COMPONENT_CHECK(Resource);
	return Resource->GetCurrent(Type);
}

int Monster::GetMaxResource(EResourceType Type) const
{
	COMPONENT_CHECK(Resource);
	return Resource->GetMax(Type);
}

std::string Monster::GetName() const
{
	return MonsterData.Name;
}

int Monster::GetActionSpeed() const
{
	return GetStat(EStatType::ActionSpeed);
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