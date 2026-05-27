#pragma once

class IUnitStat
{
public:
	virtual int GetStat(enum class EStatType Type) const = 0;
	virtual void ApplyStat(enum class EStatType Type, int Delta) = 0;
};
