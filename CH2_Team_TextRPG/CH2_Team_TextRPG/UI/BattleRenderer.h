#pragma once

#include <string>
#include <vector>

class BattleRenderer
{
public:
    BattleRenderer();

    void SetMonsterName(const std::string& monsterName);

    void DrawBattleScreen();
    void DrawMonsterIdle();
    void PlayMonsterAttackAnimation();
    void PlayMonsterHitAnimation();
    void PlayMonsterDeathAnimation();

    void PlayNormalBattleAnimation();

private:
    static constexpr int BattleAreaX = 30;
    static constexpr int BattleAreaY = 0;
    static constexpr int BattleAreaWidth = 180;
    static constexpr int BattleAreaHeight = 34;
    static constexpr int MonsterDrawX = BattleAreaX + 40;
    static constexpr int MonsterDrawY = BattleAreaY + 5;

    std::string CurrentMonsterName;

    void ClearBattleArea();
    void DrawFrameAt(int x, int y, const std::vector<std::string>& frame);
    void DrawBattleTitle();

    std::vector<std::string> GetMonsterIdleFrame() const;
    std::vector<std::string> GetMonsterHitFrame() const;
    std::vector<std::string> GetMonsterAttackFrame() const;
};
