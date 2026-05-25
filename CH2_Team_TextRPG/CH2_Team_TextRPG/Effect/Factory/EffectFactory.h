#pragma once
#include <functional>
#include "Manager/InputManager.h"
#include "Manager/LogManager.h"

class IEffect;

class EffectFactory
{
public:
	typedef IEffect* (*CreateFunc)(int);

	static std::unordered_map<std::string, CreateFunc>& GetRegistry() 
	{
		static std::unordered_map<std::string, CreateFunc> registry;
		return registry;
	}

	static bool RegisterEffect(const std::string& Tag, CreateFunc Creator)
	{
		GetRegistry().insert_or_assign(Tag, Creator);
		return true;
	}

	static IEffect* CreateEffect(const std::string& Tag, int Value)
	{
		auto& registry = GetRegistry();
		auto it = registry.find(Tag);

		if (it != registry.end())
		{
			IEffect* newEffect = it->second(Value);
			return it->second(Value);
		}

		GInput << "[Effect Factory] Invalid Tag " << Tag << "\n";
		GLog.AddLog("[Effect Factory] Invalid Tag" + Tag);

		return nullptr;
	}
};