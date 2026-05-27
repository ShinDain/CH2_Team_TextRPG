#pragma once
#include <nlohmann/json.hpp>

#define RESOURCE_TYPE(X)	\
	X(Health)				\
	X(Mana)					\

#define RESOURCE_TYPES(Name) Name,
enum class EResourceType
{
	RESOURCE_TYPE(RESOURCE_TYPES)
	Max
};

enum class EStatType
{
	Attack = 0,
	Defense,
	ActionSpeed,
	RESOURCE_TYPE(RESOURCE_TYPES)
	Max
};
#undef RESOURCE_TYPES

constexpr bool IsResourceType(EStatType Type)
{
#define RESOURCE_TYPE_CHECK(Name) case EStatType::Name: return true;
	switch (Type)
	{
		RESOURCE_TYPE(RESOURCE_TYPE_CHECK)
		default: return false;
	}
#undef RESOURCE_TYPE_CHECK
}

constexpr EResourceType ToResourceType(EStatType Type)
{
#define RESOURCE_TYPE_CONV(Name) case EStatType::Name: return EResourceType::Name;
	switch (Type)
	{
		RESOURCE_TYPE(RESOURCE_TYPE_CONV)
		default: return EResourceType::Max;
	}
#undef RESOURCE_TYPE_CONV
}

constexpr EStatType ToStatType(EResourceType Type)
{
#define STAT_TYPE_CONV(Name) case EResourceType::Name: return EStatType::Name;
	switch (Type)
	{
		RESOURCE_TYPE(STAT_TYPE_CONV)
		default: return EStatType::Max;
	}
#undef STAT_TYPE_CONV
}

#define RESOURCE_TYPE_ENUM(Name) { EStatType::Name, #Name },
NLOHMANN_JSON_SERIALIZE_ENUM(EStatType, {
	{EStatType::Attack, "Attack"},
	{EStatType::Defense, "Defense"},
	RESOURCE_TYPE(RESOURCE_TYPE_ENUM)
	{EStatType::ActionSpeed, "ActionSpeed"},
})
#undef RESOURCE_TYPE_ENUM

#undef RESOURCE_TYPE
