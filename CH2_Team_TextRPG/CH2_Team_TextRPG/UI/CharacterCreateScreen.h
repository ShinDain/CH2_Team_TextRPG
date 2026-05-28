#pragma once

#include "Data/Character/CharacterJobData.h"
#include <vector>

class CharacterCreateScreen
{
public:
	static void DrawJobSelectionScreen(const std::vector<CharacterJobData>& Jobs);
};
