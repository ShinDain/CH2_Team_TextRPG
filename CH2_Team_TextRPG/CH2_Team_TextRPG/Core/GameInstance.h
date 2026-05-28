#pragma once

#include "Map/MapManager.h"
#include "Manager/LogManager.h"
#include "Combat/BattleStartData.h"

class InputManager;
class Player;

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
    Player* GetMainPlayer() const;

	void SetBattleStartData(const BattleStartData& InBattleStartData);
	const BattleStartData* GetBattleStartData() const;
	void ClearBattleStartData();
    
    InputManager* GetInputManager() const { return GameInputManager; }

private:
	bool InitializeManager();
	bool InitializeDataTable();

protected:
    bool IsRunning;

    MapManager Map;
    LogManager Log;
	BattleStartData CurrentBattleStartData;
	bool bHasBattleStartData = false;
    
    InputManager* GameInputManager;  

	class Player* MainPlayer;
};

inline class Player* GetMainPlayer()
{
	return GameInstance::GetInstance().GetMainPlayer();
}
