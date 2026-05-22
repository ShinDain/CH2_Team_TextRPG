#pragma once

#include "../Map/MapManager.h"
#include "../Log/LogManager.h"

class GameInstance
{
private:
    GameInstance();
    GameInstance(const GameInstance& rhs) = delete;
    GameInstance& operator=(const GameInstance& rhs) = delete;

public:
    virtual ~GameInstance();

    static GameInstance& GetInstance();

    bool Initialize();

    void RunLoop();
    void ShutDown();

protected:
    bool IsRunning;

    MapManager Map;
    LogManager Log;
};