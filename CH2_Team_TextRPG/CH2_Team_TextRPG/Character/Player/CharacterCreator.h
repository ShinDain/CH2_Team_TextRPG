#pragma once

#include "Data/Character/CharacterJobData.h"

class GameInstance;
class Player;

class CharacterCreator
{
public:
	static bool CreatePlayerFromJob(GameInstance& Instance, const CharacterJobData& SelectedJob);

private:
	static void ApplyCharacterStats(Player& MainPlayer, const CharacterStatsData& Stats);
};
