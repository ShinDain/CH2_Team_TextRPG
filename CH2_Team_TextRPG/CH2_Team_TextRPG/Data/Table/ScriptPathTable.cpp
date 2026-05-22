#include "pch.h"
#include "ScriptPathTable.h"

ScriptPathTable::ScriptPathTable()
{
}

ScriptPathTable::~ScriptPathTable()
{
}

ScriptPathTable& ScriptPathTable::GetInstance()
{
	static ScriptPathTable Instance;
	return Instance;
}

void ScriptPathTable::ParseData(const json& InData)
{
	for (const json& data : InData[KEY_FILEPATHS])
	{
		std::string category = data[KEY_CATEGORY];
		PathMap.emplace(category, std::vector<std::string>());

		std::string filePath;
		for (const json& name : data[KEY_NAME])
		{
			filePath = SCRIPT_FILE_PATH_PREFIX + category;
			filePath += "/";
			filePath += name;

			PathMap[category].push_back(filePath);
		}
	}
}
