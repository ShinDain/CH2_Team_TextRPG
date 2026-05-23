#pragma once

class IUnitStat
{
public:
	virtual int GetStat(enum class EStatType Type) const = 0;
};
