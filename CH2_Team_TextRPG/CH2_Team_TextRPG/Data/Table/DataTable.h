#pragma once
#include "../JsonDataParser.h"

class IDataTable
{
public:
	virtual bool Load(const std::string& FilePath) = 0;

protected:
	virtual void ParseData(const json& InData) = 0;
};

class BaseDataTable : IDataTable
{
public:
	virtual bool Load(const std::string& FilePath) override;
};