#include "pch.h"
#include "ShopCondition.h"

void ShopCondition::Init()
{
	SimpleTriggerCondition::Init();
}

void ShopCondition::OnNotify()
{
	SimpleTriggerCondition::OnNotify();
}

bool ShopCondition::Check()
{
    return SimpleTriggerCondition::Check();
}
