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
	for (const json& data : InData["filepaths"])
	{
		std::string category = data["category"];
		PathMap.emplace(category, std::vector<std::string>());

		std::string filePath;
		for (const json& name : data["name"])
		{
			filePath = "../Script/" + category;
			filePath += "/";
			filePath += name;

			PathMap[category].push_back(filePath);
		}
	}
}
