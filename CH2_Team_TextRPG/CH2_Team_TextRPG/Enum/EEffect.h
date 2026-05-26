#pragma once
#include <cstdint>
#include "nlohmann/json.hpp"

enum class ETargetType : uint8_t 
{
	SELF = 0,           // 자신
	SINGLE_ENEMY = 1,    // 적 단일
	ALL_ENEMIES = 2,     // 적 전체
	SINGLE_ALLY = 3,     // 아군 단일
	ALL_ALLIES = 4       // 아군 전체
};

NLOHMANN_JSON_SERIALIZE_ENUM(ETargetType, {
	{ETargetType::SELF, "SELF"},
	{ETargetType::SINGLE_ENEMY, "SINGLE_ENEMY"},
	{ETargetType::ALL_ENEMIES, "ALL_ENEMIES"},
	{ETargetType::SINGLE_ALLY, "SINGLE_ALLY"},
	{ETargetType::ALL_ALLIES, "ALL_ALLIES"}
	});