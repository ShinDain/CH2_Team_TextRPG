#include "pch.h"
#include "HealthComponent.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"

HealthComponent::HealthComponent(Object* InOwner) :
	Component(InOwner,"Health"),
	CurrentHP(0)
{
	UnitStat = dynamic_cast<const IUnitStat*>(InOwner);	
}

HealthComponent::~HealthComponent()
{
}

bool HealthComponent::Initialize()
{
	if (!UnitStat)
	{
		GLog.AddLog("Failed: UnitStat Is Null");
		GLog.PrintAllLogs();
		return false;
	}
	
	CurrentHP = UnitStat->GetStat(EStatType::MaxHP);
	
	return true;
}

int HealthComponent::GetMax() const
{
	return UnitStat->GetStat(EStatType::MaxHP);
}

void HealthComponent::Increase(int Amount)
{
	if (Amount < 0)
	{
		return;
	}
	int MaxHP = GetMax();
	CurrentHP = std::min(CurrentHP + Amount, MaxHP);
	
}

void HealthComponent::Decrease(int Amount)
{
	if (Amount < 0)
	{
		return;
	}
	CurrentHP = std::max(CurrentHP - Amount, 0);
}

void HealthComponent::Restore()
{
	CurrentHP = GetMax();
}
