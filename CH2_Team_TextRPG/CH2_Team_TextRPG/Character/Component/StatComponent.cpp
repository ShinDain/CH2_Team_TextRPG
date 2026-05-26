#include "pch.h"
#include "StatComponent.h"
#include "Data/Character/Stat.h"

StatComponent::StatComponent(Object* InOwner) :
	Component(InOwner, "Stat"),
	Stats(static_cast<int>(EStatType::Max))
{
	
}

StatComponent::~StatComponent()
{
	
}

const size_t StatComponent::StatTypeToIndex(EStatType InType)
{
	const size_t Idx = static_cast<size_t>(InType);
	assert(Idx < static_cast<size_t>(EStatType::Max) && "EStatType 범위 초과");
	return Idx;
}

int StatComponent::GetStat(EStatType InType)
{
	const size_t Idx = StatTypeToIndex(InType);
	return Stats[Idx];
}

void StatComponent::SetStat(EStatType InType, int Value)
{
	const size_t Idx = StatTypeToIndex(InType);
	Stats[Idx] = Value;
}

void StatComponent::AddStat(EStatType InType, int Delta)
{
	const size_t Idx = StatTypeToIndex(InType);
	Stats[Idx] += Delta;
}

bool StatComponent::Initialize()
{
	return true;
}
