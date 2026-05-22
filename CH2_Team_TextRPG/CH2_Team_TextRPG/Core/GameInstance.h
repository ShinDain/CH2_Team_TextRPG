#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"

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
