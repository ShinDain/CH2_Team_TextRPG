#pragma once

struct BattleMonsterView
{
    std::string MonsterName;
    int DrawX;
    int DrawY;
    int CurrentHP;
    int MaxHP;
};

class BattleRenderer
{
public:
    BattleRenderer();

    void SetMonsterName(const std::string& monsterName);
    void ClearMonsters();
    void AddMonster(const std::string& monsterName, int drawX, int drawY, int currentHP, int maxHP);
    void DrawAllMonsterIdle();
    void SetMonsterHP(int monsterIndex, int currentHP);
    void DecreaseMonsterHP(int monsterIndex, int amount);

    void DrawBattleScreen();
    void DrawMonsterIdle();
    void PlayMonsterAttackAnimation();
    void PlayMonsterAttackAnimation(int monsterIndex);
    void PlayMonsterHitAnimation();
    void PlayMonsterHitAnimation(int monsterIndex);
    void PlayMonsterDeathAnimation();

    void PlayNormalBattleAnimation();

private:
    static constexpr int BattleAreaX = 30;
    static constexpr int BattleAreaY = 0;
    static constexpr int BattleAreaWidth = 180;
    static constexpr int BattleAreaHeight = 34;
    static constexpr int MonsterAreaX = BattleAreaX + 1;
    static constexpr int MonsterAreaY = BattleAreaY + 4;
    static constexpr int MonsterAreaWidth = BattleAreaWidth - 2;
    static constexpr int MonsterAreaHeight = BattleAreaHeight - 6;
    static constexpr int MonsterDrawX = BattleAreaX + 40;
    static constexpr int MonsterDrawY = BattleAreaY + 5;

    std::string CurrentMonsterName;
    std::vector<BattleMonsterView> MonsterViews;

    void ClearBattleArea();
    void ClearMonsterArea();
    void DrawMonsterFrame(const std::vector<std::string>& frame);
    void DrawMonsterFrameAt(
        const BattleMonsterView& monsterView,
        const std::string& state,
        int offsetX = 0,
        int offsetY = 0
    );
    void DrawMonsterStatusAt(const BattleMonsterView& monsterView, int x, int y);
    void DrawFrameAt(int x, int y, const std::vector<std::string>& frame);
    void DrawBattleTitle();

    std::vector<std::string> GetMonsterIdleFrame() const;
    std::vector<std::string> GetMonsterHitFrame() const;
    std::vector<std::string> GetMonsterAttackFrame() const;
};
