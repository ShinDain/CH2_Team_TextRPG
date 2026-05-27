#include "pch.h"
#include "ResourceComponent.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"

ResourceComponent::ResourceComponent(Object* InOwner) :
	Component(InOwner, "Resource"),
	UnitStat(nullptr),
	Currents(static_cast<size_t>(EResourceType::Max), 0)
{
	UnitStat = dynamic_cast<const IUnitStat*>(InOwner);
}

ResourceComponent::~ResourceComponent()
{
}

bool ResourceComponent::Initialize()
{
	if (!UnitStat)
	{
		GLog.AddLog("Failed: UnitStat Is Null");
		GLog.PrintAllLogs();
		return false;
	}

	Restore();
	return true;
}

int ResourceComponent::GetCurrent(EResourceType Type) const
{
	return Currents[static_cast<size_t>(Type)];
}

int ResourceComponent::GetMax(EResourceType Type) const
{
	if (!UnitStat) return 0;
	return UnitStat->GetStat(ToStatType(Type));
}

void ResourceComponent::Increase(EResourceType Type, int Amount)
{
	if (Amount < 0)
	{
		return;
	}
	const int Max = GetMax(Type);
	int& Cur = Currents[static_cast<size_t>(Type)];
	Cur = std::min(Cur + Amount, Max);
}

void ResourceComponent::Decrease(EResourceType Type, int Amount)
{
	if (Amount < 0)
	{
		return;
	}
	int& Cur = Currents[static_cast<size_t>(Type)];
	Cur = std::max(Cur - Amount, 0);
}

void ResourceComponent::Restore(EResourceType Type)
{
	Currents[static_cast<size_t>(Type)] = GetMax(Type);
}

void ResourceComponent::Restore()
{
	for (size_t i = 0; i < Currents.size(); ++i)
	{
		Currents[i] = GetMax(static_cast<EResourceType>(i));
	}
}
