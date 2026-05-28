#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct BattleMonsterStartData
{
	uint32_t MonsterId = 0;
	std::string Name;
	int HP = 0;
	int Attack = 0;
	int Defense = 0;
	std::string Type;
};

struct BattleStartData
{
	bool bIsBoss = false;
	int Floor = 0;
	std::vector<BattleMonsterStartData> Monsters;
};
