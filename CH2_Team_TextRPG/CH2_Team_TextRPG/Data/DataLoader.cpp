#include "pch.h"
#include "DataLoader.h"
#include "Data/Table/ItemDataTable.h"
#include "Data/Table/MonsterDataTable.h"
#include "Data/Table/SkillDataTable.h"
#include "Data/Table/ScriptPathTable.h"
#include "Table/PlayerDataTable.h"

bool DataLoader::LoadInitialGameData()
{
	if (!ScriptPathTable::GetInstance().Load(Game::DataPaths::ScriptList))
		return false;

	for (const std::string& path : ScriptPathTable::GetInstance().GetFilePaths(Game::DataPaths::Item))
	{
		ItemDataTable::GetInstance().Load(path);
	}

	for (const std::string& path : ScriptPathTable::GetInstance().GetFilePaths(Game::DataPaths::Monster))
	{
		MonsterDataTable::GetInstance().Load(path);
	}

	for (const std::string& path : ScriptPathTable::GetInstance().GetFilePaths(Game::DataPaths::Skill))
	{
		SkillDataTable::GetInstance().Load(path);
	}

	/*for (const std::string& path : ScriptPathTable::GetInstance().GetFilePaths(DATA_CATEGORY_MAP))
	{
		MapDataTable::GetInstance().Load(path);
	}*/
	
	for (const std::string& path : ScriptPathTable::GetInstance().GetFilePaths(Game::DataPaths::Player))
	{
		PlayerDataTable::GetInstance().Load(path);
	}

    return true;
}
