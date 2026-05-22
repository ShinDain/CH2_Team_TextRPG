#pragma once
#include "DataTable.h"

class ScriptPathTable final : public BaseDataTable
{
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
