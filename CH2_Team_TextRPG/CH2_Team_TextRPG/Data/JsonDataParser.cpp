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

bool JsonDataParser::Save(const std::string& FilePath, const json& InJsonData)
{
	std::ofstream File(FilePath);
	if (!File)
	{
		GLog.AddLog("SaveFailed! ");
		GLog.AddLog("FilePaht: ");
		GLog.AddLog(FilePath);
		return false;
	}

	try
	{
		File << InJsonData.dump(4);	
	}
	catch (const json::exception& Exception)
	{
		std::cerr << "JSON 파일 파싱 실패: " << FilePath << "\n";
		std::cerr << Exception.what() << "\n";
		File.close();
	}
	File.close();
	
	return true;
}

