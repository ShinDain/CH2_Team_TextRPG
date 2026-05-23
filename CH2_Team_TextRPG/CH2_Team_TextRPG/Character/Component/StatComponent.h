#pragma once
#include "Core/Component.h"

class StatComponent : public Component
{
public:
	StatComponent(Object* InOwner);
	~StatComponent() override;
	
	bool Initialize() override;
};