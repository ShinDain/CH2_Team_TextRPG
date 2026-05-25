#pragma once

#include <vector>
#include <string>

class BattleRenderer
{
public:
    void DrawBattleScreen();
    void DrawMonsterIdle();

    void PlayPlayerAttackAnimation();
    void PlayMonsterHitAnimation();
    void PlayMonsterDeathAnimation();

    void PlayNormalBattleAnimation();

private:
    static constexpr int BattleAreaX = 30;
    static constexpr int BattleAreaY = 0;
    static constexpr int BattleAreaWidth = 180;
    static constexpr int BattleAreaHeight = 34;

    void ClearBattleArea();
    void DrawFrameAt(int x, int y, const std::vector<std::string>& frame);
    void DrawBattleTitle();
};