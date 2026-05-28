#pragma once

#include <string>
#include <vector>

struct CharacterStatsData
{
	int Health = 0;
	int Mana = 0;
	int Attack = 0;
	int Defense = 0;
	int ActionSpeed = 0;
};

struct StartItemData
{
	int ItemId = 0;
	int Count = 0;
};

struct CharacterJobData
{
	int Id = 0;
	std::string JobName;
	std::string Description;
	CharacterStatsData Stats;
	std::vector<int> StartSkillIds;
	std::vector<StartItemData> StartItems;
};
