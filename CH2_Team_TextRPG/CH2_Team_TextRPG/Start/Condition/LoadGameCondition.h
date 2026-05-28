#pragma once
#include "Core/Condition.h"

class LoadGameCondition : public ICondition
{
public:
	LoadGameCondition();
	~LoadGameCondition() override;
	
	void Init() override;
	void OnNotify() override;
	bool Check() override;
};
