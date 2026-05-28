#pragma once

#include "Map/MapManager.h"
#include "Combat/BattleSystem.h"
#include <string>
#include <vector>

class LogManager;
class Player;

struct FCommandOption
{
    std::string Text;
    bool bIsUsable = true;
};

class GameScreen
{
public:
    static void DrawMainScreen(const MapManager& Map, const LogManager& Log, const Player* MainPlayer);
    static void DrawBattleCommandPanel(const std::string& PanelTitle, const std::vector<FCommandOption>& Options);
    static void DrawCharacterPanel(const Player* MainPlayer);
    static void DrawInventoryPanel(const Player* MainPlayer);
    static void DrawLogPanel(const LogManager& Log);

private:
    static void DrawMapPanel(const MapManager& Map);
    static void DrawNavigationPanel(const MapManager& Map);
    static void DrawInputPanel();
};
