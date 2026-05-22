#pragma once
#include "DataTable.h"

const std::string SCRIPT_FILE_PATH_PREFIX = "../Script/";

class ScriptPathTable final : public BaseDataTable
{
private:
	static constexpr const char* KEY_FILEPATHS = "Filepaths";
	static constexpr const char* KEY_CATEGORY = "Category";
	static constexpr const char* KEY_NAME = "Name";

private:
	ScriptPathTable();
public:
	~ScriptPathTable();

	static ScriptPathTable& GetInstance();
	
	const std::vector<std::string> GetFilePaths(const std::string& Category) { return PathMap[Category]; }

protected:
	virtual void ParseData(const json& InData) override;
	
protected:
	std::unordered_map<std::string, std::vector<std::string>> PathMap;
};
