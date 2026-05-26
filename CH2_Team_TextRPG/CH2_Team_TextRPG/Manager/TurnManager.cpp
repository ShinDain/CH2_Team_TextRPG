#include "pch.h"
#include <algorithm>
#include "TurnManager.h"
#include "Character/Character.h"
#include "Combat/State_Battle.h"
#include "Character/Component/StatComponent.h"
#include "Data/Character/Stat.h"
#include "Character/Interface/UnitStat.h"

TurnManager::~TurnManager()
{
	turnQueue.clear();
}

void TurnManager::AddCharacterToTimeline(Character* character)
{
	if (character == nullptr) return;
	float initialActionValue = TurnThreshold / GetCharacterSpeed(character);
	turnQueue.push_back(FTimelineNode{ character, initialActionValue });
}

Character* TurnManager::GetNextTurnCharacter()
{
	if (turnQueue.empty()) return nullptr;
	sort(turnQueue.begin(), turnQueue.end());

	float TimePassed = turnQueue.front().ActionValue;
	for (auto& node : turnQueue)
	{
		node.ActionValue -= TimePassed;
	}
    return turnQueue.front().unit;
}

void TurnManager::ResetCharacterTurn(Character* character)
{
	if (character == nullptr) return;

	for(auto& it : turnQueue)
	{
		if (it.unit == character)
		{
			it.ActionValue = TurnThreshold / GetCharacterSpeed(character);
			break;
		}
	}
}

void TurnManager::AddActionValue(Character* character, float value)
{
	if (character == nullptr) return;
	for (auto& node : turnQueue)
	{
		if (node.unit == character)
		{
			node.ActionValue += value;
			break;
		}
	}
}

float TurnManager::GetCharacterSpeed(Character* character) const
{
	float speed = 1.0f;
	IUnitStat* StatInterface = dynamic_cast<IUnitStat*>(character);
	if (StatInterface != nullptr)
	{
		speed = StatInterface->GetStat(EStatType::ActionSpeed);
		if (speed <= 0) speed = 1.0f;
	}
	return speed;
}
