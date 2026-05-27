#pragma once

class ILevelable
{
public:
	virtual ~ILevelable() = default;
	virtual void AddExp(int Amount) = 0;
	virtual int  GetLevel() const = 0;
	virtual int  GetExp() const = 0;
	virtual bool IsMaxLevel() const = 0;
};
