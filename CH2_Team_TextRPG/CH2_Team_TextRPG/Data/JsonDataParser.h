#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JsonDataParser
{
public:
	static bool Load(const std::string& FilePath, json& OutJsonData);

};

