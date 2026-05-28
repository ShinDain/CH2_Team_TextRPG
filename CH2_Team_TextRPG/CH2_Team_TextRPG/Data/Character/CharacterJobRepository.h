#pragma once

#include "Data/Character/CharacterJobData.h"
#include <vector>

class LogManager;

class CharacterJobRepository
{
public:
	static bool LoadCharacterJobs(std::vector<CharacterJobData>& OutJobs, LogManager& Log);
};
