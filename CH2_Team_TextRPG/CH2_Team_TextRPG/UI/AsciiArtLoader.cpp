#include "pch.h"
#include "UI/AsciiArtLoader.h"

#include <filesystem>
#include <fstream>

std::vector<std::string> AsciiArtLoader::LoadFrame(
    const std::string& monsterName,
    const std::string& stateName
)
{
    std::vector<std::string> frame;
    std::vector<std::string> checkedPaths;

    const std::string fileName = monsterName + "_" + stateName + ".txt";
    const std::vector<std::filesystem::path> candidatePaths =
    {
        std::filesystem::path("Resources") / "Ascii" / fileName,
        std::filesystem::path("CH2_Team_TextRPG") / "Resources" / "Ascii" / fileName,
        std::filesystem::path("..") / "CH2_Team_TextRPG" / "Resources" / "Ascii" / fileName,
        std::filesystem::path("..") / ".." / "CH2_Team_TextRPG" / "Resources" / "Ascii" / fileName,
        std::filesystem::path("..") / ".." / "Resources" / "Ascii" / fileName
    };

    for (const std::filesystem::path& candidatePath : candidatePaths)
    {
        const std::filesystem::path absolutePath = std::filesystem::absolute(candidatePath);
        const std::string pathString = absolutePath.string();

        checkedPaths.push_back(pathString);

        if (!std::filesystem::exists(candidatePath))
        {
            continue;
        }

        std::ifstream file(candidatePath);

        if (!file.is_open())
        {
            continue;
        }

        std::string line;

        while (std::getline(file, line))
        {
            frame.push_back(line);
        }

        return frame;
    }

    frame.push_back("[ASCII FILE NOT FOUND]");
    frame.push_back("monsterName: " + monsterName);
    frame.push_back("state: " + stateName);
    frame.push_back("checked paths:");

    for (const std::string& checkedPath : checkedPaths)
    {
        frame.push_back("- " + checkedPath);
    }

    return frame;
}
