#pragma once

#include "Character/Monster/Monster.h"

class MonsterFactory
{
public:
	static Monster* CreateForPlayer(const std::string& Name, Player* player);
};


