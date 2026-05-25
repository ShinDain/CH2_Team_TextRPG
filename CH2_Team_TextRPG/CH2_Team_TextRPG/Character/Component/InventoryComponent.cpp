#include "pch.h"
#include "InventoryComponent.h"

InventoryComponent::InventoryComponent(Object* InOwner)
	:Component(InOwner, "Inventory")
{
}

InventoryComponent::~InventoryComponent()
{
}

bool InventoryComponent::Initialize()
{
    return false;
}

bool InventoryComponent::UseItem()
{
	return false;
}

void InventoryComponent::AcqireItem(const std::string ItemName)
{
}

std::vector<std::string_view> InventoryComponent::GetItemList()
{
	std::vector<std::string_view> List{};

	return List;
}
