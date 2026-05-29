#pragma once
#include "Core/Condition.h"

class StartNextCondition : public AlwaysTrueCondition
{
public:
	~StartNextCondition() override;
	void Init() override;
	void OnNotify() override;
	bool Check() override;
};
