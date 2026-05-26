#pragma once

#include "nlohmann/json.hpp"

struct EffectData
{
public:
	std::string Tag;
	int Value;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EffectData, Tag, Value);