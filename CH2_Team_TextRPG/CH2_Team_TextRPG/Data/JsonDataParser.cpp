#include "pch.h"
#include <fstream>
#include "JsonDataParser.h"

bool JsonDataParser::Load(const std::string& FilePath, json& OutJsonData)
{
	std::ifstream InFile(FilePath);

	if (!InFile)
	{
		std::cerr << "파일을 열 수 없습니다.";
		return false;
	}

	InFile >> OutJsonData;

	InFile.close();

	return true;
}
