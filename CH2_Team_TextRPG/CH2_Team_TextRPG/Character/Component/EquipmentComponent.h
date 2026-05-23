#pragma once
#include "Core/Component.h"

class EquipmentComponent : public Component
{
public:
	EquipmentComponent(Object* InOwner);
	~EquipmentComponent() override;
	
	void Initialize() override;
};
