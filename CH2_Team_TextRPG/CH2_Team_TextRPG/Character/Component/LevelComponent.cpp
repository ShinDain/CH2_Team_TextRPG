#include "pch.h"
#include "LevelComponent.h"

#include "Character/Component/StatComponent.h"
#include "Character/Interface/Resource.h"
#include "Data/Character/Stat.h"
#include "Data/Table/LevelDataTable.h"

LevelComponent::LevelComponent(Object* InOwner) :
	Component(InOwner, "Level"),
	CurrentLevel(0),
	MaxLevel(0),
	CurrentExp(0)
{
}

LevelComponent::~LevelComponent()
{
	OnLevelUp = nullptr;
}

bool LevelComponent::Initialize()
{
	CurrentLevel = 1;
	CurrentExp = 0;
	return true;
}

bool LevelComponent::IsMaxLevel() const
{
	return CurrentLevel >= LevelDataTable::GetInstance().GetMaxLevel();
}

void LevelComponent::SetExp(int NewExp)
{
	if (NewExp <= 0) 
		return;
	
	CurrentExp = NewExp;
}

int LevelComponent::GetExpToNextLevel() const
{
	if (IsMaxLevel())
	{
		return 0;
	}

	const LevelData* Next = LevelDataTable::GetInstance().FindByLevel(CurrentLevel + 1);
	if (!Next) return 0;
	return std::max(0, Next->Exp - CurrentExp);
}

void LevelComponent::BindOnLevelUp(const OnLevelUpCallback& Subscriber)
{
	OnLevelUp = Subscriber;
}

void LevelComponent::UnbindOnLevelup()
{
	OnLevelUp = nullptr;
}

void LevelComponent::AddExp(int Amount)
{
	if (Amount <= 0 || IsMaxLevel()) return;
	CurrentExp += Amount;
	CheckLevelUp();
}

void LevelComponent::ReviveLevel(int TargetLevel)
{
	while (CurrentLevel < TargetLevel && !IsMaxLevel())
	{
		LevelUp();
	}
}

void LevelComponent::CheckLevelUp()
{
	const LevelDataTable& LevelDataTable = LevelDataTable::GetInstance();
	while (!IsMaxLevel())
	{
		const LevelData* Next = LevelDataTable.FindByLevel(CurrentLevel + 1);
		if (!Next) break;
		if (CurrentExp < Next->Exp) break;

		CurrentExp -= Next->Exp;
		LevelUp();
	}
	if (IsMaxLevel())
	{
		CurrentExp = 0;
	}
}

void LevelComponent::LevelUp()
{
	const int NewLevel = CurrentLevel + 1;
	ApplyLevelupEvent(NewLevel);
	CurrentLevel = NewLevel;

	if (OnLevelUp) OnLevelUp(CurrentLevel);
}

void LevelComponent::ApplyLevelupEvent(int Level)
{
	if (const LevelData* Data = LevelDataTable::GetInstance().FindByLevel(Level))
	{
		if (std::shared_ptr<StatComponent> StatComp = Owner->FindComponent<StatComponent>("Stat"))
		{
			for (auto Stat : Data->Stats)
			{
				EStatType Type = StringToEStatType(Stat.first);
				if (Type == EStatType::Max) continue;
				StatComp->AddStat(Type, Stat.second);
			}
		}
		if (auto* Resource = dynamic_cast<IResource*>(Owner))
		{
			Resource->RestoreAll();
		}	
	}
}
