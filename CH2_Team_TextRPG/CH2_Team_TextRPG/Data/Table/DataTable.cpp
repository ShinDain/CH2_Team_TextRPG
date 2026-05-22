#include "pch.h"
#include "DataTable.h"

bool BaseDataTable::Load(const std::string& FilePath)
{
	json jsonData;
	if(!JsonDataParser::Load(FilePath, jsonData))
	{
		return false;
	}

	ParseData(jsonData);

	return true;
}
