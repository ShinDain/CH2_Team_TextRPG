#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"

class InputManager;
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

    MapManager& GetMapManager();
    LogManager& GetLogManager();
    
    InputManager* GetInputManager() const { return GameInputManager; }

	std::shared_ptr<class Player> GetMainPlayer() const { return MainPlayer; }
private:
	bool InitializeManager();
	bool InitializeDataTable();

protected:
    bool IsRunning;

    MapManager Map;
    LogManager Log;
    
    InputManager* GameInputManager;  

	std::shared_ptr<class Player> MainPlayer;
};

inline std::shared_ptr<class Player> GetMainPlayer()
{
	return GameInstance::GetInstance().GetMainPlayer();
}