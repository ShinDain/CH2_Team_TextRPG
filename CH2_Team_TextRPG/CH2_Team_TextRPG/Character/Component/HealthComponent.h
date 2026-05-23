#pragma once
#include "Core/Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent(Object* InOwner, const class StatComponent* InStat);
	~HealthComponent() override;
	
	void Initialize() override;
};
