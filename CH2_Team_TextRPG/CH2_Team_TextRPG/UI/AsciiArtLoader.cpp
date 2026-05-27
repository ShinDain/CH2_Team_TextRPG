#include "pch.h"
#include "UI/AsciiArtLoader.h"

#include <filesystem>
#include <fstream>
#include <windows.h>

namespace
{
std::filesystem::path GetExecutableDirectory()
{
    char modulePath[MAX_PATH] = {};
    const DWORD length = GetModuleFileNameA(nullptr, modulePath, MAX_PATH);

    if (length == 0 || length == MAX_PATH)
    {
        return {};
    }

    return std::filesystem::path(modulePath).parent_path();
}

void AddAsciiPathCandidates(
    std::vector<std::filesystem::path>& candidatePaths,
    const std::filesystem::path& basePath,
    const std::string& fileName
)
{
    if (basePath.empty())
    {
        return;
    }

    candidatePaths.push_back(basePath / "Resources" / "Ascii" / fileName);

    if (basePath.has_parent_path())
    {
        candidatePaths.push_back(basePath.parent_path() / "Resources" / "Ascii" / fileName);
    }

    if (basePath.has_parent_path() && basePath.parent_path().has_parent_path())
    {
        candidatePaths.push_back(basePath.parent_path().parent_path() / "Resources" / "Ascii" / fileName);
    }
}
}

std::vector<std::string> AsciiArtLoader::LoadFrame(
    const std::string& monsterName,
    const std::string& stateName
)
{
    const std::string fileName = monsterName + "_" + stateName + ".txt";
    std::vector<std::filesystem::path> candidatePaths;

    AddAsciiPathCandidates(candidatePaths, std::filesystem::current_path(), fileName);
    AddAsciiPathCandidates(candidatePaths, GetExecutableDirectory(), fileName);

    for (const std::filesystem::path& candidatePath : candidatePaths)
    {
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
        std::vector<std::string> frame;

        while (std::getline(file, line))
        {
            frame.push_back(line);
        }

        return frame;
    }

    return { "ASCII FILE NOT FOUND" };
}
