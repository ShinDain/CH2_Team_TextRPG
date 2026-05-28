#pragma once
#include <nlohmann/json.hpp>
#include "Character/Component/InventoryComponent.h"

struct UserData
{
	UserData() : MapIndex(0), ClassIndex(0), Level(1), Exp(0), Gold(0) {}

	std::string UserName;
	int MapIndex;
	int ClassIndex;
	int Level;
	int Exp;
	int Gold;

	std::vector<uint16_t> Skills;
	std::map<std::string, int> OwnedItems;
	std::map<EEquipmentType, int> EquippedItems;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(UserData, UserName, MapIndex, ClassIndex, Level, Exp, Gold, Skills, OwnedItems, EquippedItems);


