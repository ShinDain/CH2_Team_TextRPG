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

	try
	{
		OutJsonData = json::parse(InFile, nullptr, true, true);
	}
	catch (const json::exception& Exception)
	{
		std::cerr << "JSON 파일 파싱 실패: " << FilePath << "\n";
		std::cerr << Exception.what() << "\n";
		InFile.close();
		return false;
	}

	InFile.close();

	return true;
}

void JsonDataParser::Save(const std::string& FilePath, const json& InJsonData)
{
	std::ofstream File(FilePath);
	File << InJsonData.dump(4); 
}

