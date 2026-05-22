#include "pch.h"
#include "DataLoader.h"
#include "Data/Table/ItemDataTable.h"
#include "Data/Table/ScriptPathTable.h"

bool DataLoader::LoadInitialGameData()
{
	if (!ScriptPathTable::GetInstance().Load(INIT_FILE_PATH))
		return false;

	for (const std::string& path : ScriptPathTable::GetInstance().GetFilePaths(DATA_CATEGORY_ITEM))
	{
		ItemDataTable::GetInstance().Load(path);
	}

    return false;
}
