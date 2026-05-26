#pragma once
#include "Manager/InputManager.h"
#include "Manager/LogManager.h"
#include "Effect/EffectData.h"

class Effect;

class EffectFactory
{
public:
	typedef Effect* (*CreateFunc)(int);

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

	static Effect* CreateEffect(const EffectData& InEffectData)
	{
		std::string Tag = InEffectData.Tag;
		int Value = InEffectData.Value;

		return CreateEffect_Implement(Tag, Value);
	}

	static Effect* CreateEffect(const std::string& Tag, int Value)
	{
		return CreateEffect_Implement(Tag, Value);
	}

private: 
	static Effect* CreateEffect_Implement(const std::string& Tag, int Value)
	{
		auto& registry = GetRegistry();
		auto it = registry.find(Tag);

		if (it != registry.end())
		{
			Effect* newEffect = it->second(Value);
			return it->second(Value);
		}

		GInput << "[Effect Factory] Invalid Tag " << Tag << "\n";
		GLog.AddLog("[Effect Factory] Invalid Tag" + Tag);

		return nullptr;
	}
};