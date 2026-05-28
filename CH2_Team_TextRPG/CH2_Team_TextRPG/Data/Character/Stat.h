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

#define RESOURCE_ENUM_TO_STRING(Name) { case EStatType::Name: return #Name; }
inline std::string EStatTypeToString(EStatType Type)
{
	switch (Type) 
	{
		case EStatType::Attack: return "Attack";
		case EStatType::Defense: return "Defense";
		case EStatType::ActionSpeed: return "ActionSpeed";
		RESOURCE_TYPE(RESOURCE_ENUM_TO_STRING)
		default: assert(0);
	}
	return {}; 	
}
#undef RESOURCE_ENUM_TO_STRING

#define RESOURCE_STRING_TO_ENUM(Name) if (Str == #Name) return EStatType::Name;

inline EStatType StringToEStatType(const std::string& Str)
{
	if (Str == "Attack") return EStatType::Attack;
	if (Str == "Defense") return EStatType::Defense;
	if (Str == "ActionSpeed") return EStatType::ActionSpeed;
	RESOURCE_TYPE(RESOURCE_STRING_TO_ENUM)
	assert(0);
	return EStatType::Max;
}
#undef RESOURCE_STRING_TO_ENUM

#undef RESOURCE_TYPE
