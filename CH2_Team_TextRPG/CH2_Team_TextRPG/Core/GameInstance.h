#pragma once

#include "../Map/MapManager.h"
#include "../Log_/LogManager.h"
#include "Log_/LogManager.h"

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

	void Quit();

private:
	bool InitializeManager();

protected:
    bool IsRunning;

    MapManager Map;
    LogManager Log;
};
