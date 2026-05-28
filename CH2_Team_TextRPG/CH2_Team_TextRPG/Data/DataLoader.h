#pragma once

namespace Game
{
	namespace DataPaths
	{
		const std::string ScriptList = "../Script/ScriptList.json";
		const std::string User = "User";
		const std::string Item = "Item";
		const std::string Consumable = "Consumable";
		const std::string Equipment = "Equipment";
		const std::string Monster = "Monster";
		const std::string Player = "Player";
		const std::string Map = "Map";
		const std::string Skill = "Skill";
		const std::string Level = "Level";
	}
	
}

class DataLoader
{
	friend class GameInstance;

private:
	static bool LoadInitialGameData();
};

