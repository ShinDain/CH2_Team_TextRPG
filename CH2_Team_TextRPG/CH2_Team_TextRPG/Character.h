#pragma once
#include "pch.h"
#include "Core/Object.h"

class Character : public Object
{
public:
	Character();
	virtual ~Character();
	virtual bool Initialize();
	virtual std::string GetName() const = 0;
};
