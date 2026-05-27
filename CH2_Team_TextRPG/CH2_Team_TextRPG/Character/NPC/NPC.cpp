#include "pch.h"
#include "NPC.h"
#include "Character/Component/InventoryComponent.h"

NPC::NPC()
{
	CharacterType = ECharacterType::NPC;
	Inventory = AddComponent<InventoryComponent>(this);
}

NPC::~NPC()
{
	delete Inventory;
	Inventory = nullptr;
}

bool NPC::Initialize()
{
	Inventory->Initialize();

    return false;
}
