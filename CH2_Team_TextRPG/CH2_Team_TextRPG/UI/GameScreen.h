#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"

class GameScreen
{
public:
    static void DrawMainScreen(const MapManager& Map, const LogManager& Log);

private:
    static void DrawCharacterPanel();
    static void DrawInventoryPanel();
    static void DrawMapPanel(const MapManager& Map);
    static void DrawLogPanel(const LogManager& Log);
    static void DrawInputPanel();
};