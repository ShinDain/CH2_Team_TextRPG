#pragma once

#include "Character/Monster/Monster.h"
#include "Character/Player/Player.h"

class MonsterFactory
{
public:
	static Monster* CreateForPlayer(const std::string& Name, Player* player);
};
