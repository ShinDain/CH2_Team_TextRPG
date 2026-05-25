#pragma once

#include <vector>
#include <string>

class AnimationFrameData
{
public:
    static const std::vector<std::string>& GetSlimeIdle1();
    static const std::vector<std::string>& GetSlimeIdle2();
    static const std::vector<std::string>& GetSlimeDead();

    static const std::vector<std::string>& GetHitEffect();
};
