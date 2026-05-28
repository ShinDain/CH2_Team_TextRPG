#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"

class Player;

class GameScreen
{
public:
    static void DrawMainScreen(const MapManager& Map, const LogManager& Log, const Player* MainPlayer);

private:
    static void DrawCharacterPanel(const Player* MainPlayer);
    static void DrawInventoryPanel();
    static void DrawMapPanel(const MapManager& Map);
    static void DrawNavigationPanel(const MapManager& Map);
    static void DrawLogPanel(const LogManager& Log);
    static void DrawInputPanel();
};
