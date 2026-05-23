#pragma once
#include "pch.h"
#include "Core/Object.h"

class Character : public Object
{
public:
	Character();
	virtual ~Character();
	bool Initialize() override;
};
