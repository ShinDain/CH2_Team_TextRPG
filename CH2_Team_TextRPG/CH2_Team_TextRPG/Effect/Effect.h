#pragma once
class IEffect
{
public:
	virtual void Apply(class Object* Target) = 0;
};
