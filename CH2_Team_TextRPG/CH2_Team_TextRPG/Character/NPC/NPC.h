#pragma once
#include "Character/Character.h"

class NPC : public Character
{
public:
	NPC();
	virtual ~NPC() override;

	bool Initialize() override;

private:
	class InventoryComponent* Inventory;

};

