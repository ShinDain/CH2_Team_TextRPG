#pragma once

#include "../Map/MapManager.h"
#include "../Log/LogManager.h"

class GameProgress
{
public:
    static void HandleNodeSelection(MapManager& Map, LogManager& Log);
    static void HandleCurrentNodeEvent(const MapManager& Map, LogManager& Log);
    static void EndGame(LogManager& Log);
};