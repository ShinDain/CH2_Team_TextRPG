#pragma once
#include "Core/Condition.h"

class ShopCondition : public SimpleTriggerCondition
{
public:
	virtual void Init() override;
	virtual void OnNotify() override;
	virtual bool Check() override;
};
