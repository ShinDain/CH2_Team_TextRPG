#pragma once
class ICondition
{
public:
	virtual void Init() = 0;
	virtual void OnNotify() = 0;
	virtual bool Check() = 0;
};

class AlwaysTrueCondition : public ICondition
{
public:
	AlwaysTrueCondition();

	virtual void Init() override;
	virtual void OnNotify() override;
	virtual bool Check() override;
};