#pragma once

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
	bool InitializeDataTable();

protected:
	bool IsRunning;
};

