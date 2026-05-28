#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"
#include "Combat/BattleSystem.h"

class Player;

class GameScreen
{
public:
    static void DrawMainScreen(const MapManager& Map, const LogManager& Log, const Player* MainPlayer);
    static void DrawBattleCommandPanel(const std::vector<BattleSkillOption>& SkillOptions);
    static void DrawCharacterPanel(const Player* MainPlayer);
    static void DrawLogPanel(const LogManager& Log);

private:
    static void DrawInventoryPanel(const Player* MainPlayer);
    static void DrawMapPanel(const MapManager& Map);
    static void DrawNavigationPanel(const MapManager& Map);
    static void DrawInputPanel();
};
