#include "pch.h"
#include "Condition.h"

// Always True Condition
AlwaysTrueCondition::AlwaysTrueCondition()
{
}

void AlwaysTrueCondition::Init()
{
}

void AlwaysTrueCondition::OnNotify()
{
}

bool AlwaysTrueCondition::Check()
{
    return true;
}

// Simple Trigger Condition
SimpleTriggerCondition::SimpleTriggerCondition()
{
	bTrigger = false;
}

void SimpleTriggerCondition::Init()
{
	bTrigger = false;
}

void SimpleTriggerCondition::OnNotify()
{
	bTrigger = !bTrigger;
}

bool SimpleTriggerCondition::Check()
{
	return bTrigger;
}
