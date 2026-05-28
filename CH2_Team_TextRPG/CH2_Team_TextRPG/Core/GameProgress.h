#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"

class GameProgress
{
public:
    static bool HandleNodeSelection(MapManager& Map, LogManager& Log);
    static void HandleCurrentNodeEvent(const MapManager& Map, LogManager& Log);
    static void EndGame(LogManager& Log);
};
