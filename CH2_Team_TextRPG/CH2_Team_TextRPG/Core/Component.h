#pragma once
#include "Object.h"

class Component : public Object
{
public:
	Component() = delete;
	Component(Object* InOwner, std::string InName);
	virtual ~Component();
	virtual void Initialize() = 0;

protected:
	Object* Owner;
};
