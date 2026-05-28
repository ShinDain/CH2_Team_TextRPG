#pragma once
class ICondition
{
public:
	virtual ~ICondition() = default;
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

class SimpleTriggerCondition : public ICondition
{
public:
	SimpleTriggerCondition();

	virtual void Init() override;
	virtual void OnNotify() override;
	virtual bool Check() override;

protected:
	bool bTrigger;
};
