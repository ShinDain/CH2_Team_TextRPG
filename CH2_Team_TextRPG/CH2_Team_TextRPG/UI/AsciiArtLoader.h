#pragma once

#include <string>
#include <vector>

class AsciiArtLoader
{
public:
    static std::vector<std::string> LoadFrame(
        const std::string& monsterName,
        const std::string& stateName
    );
};