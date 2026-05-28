#pragma once
#include "Core/Condition.h"

class NewGameCondition : public ICondition
{
public:
	NewGameCondition();
	~NewGameCondition() override;
	
	void Init() override;
	void OnNotify() override;
	bool Check() override;
};
