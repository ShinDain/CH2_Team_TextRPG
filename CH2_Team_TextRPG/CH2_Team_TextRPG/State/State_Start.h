#pragma once

#include "Core/State.h"

class State_Start : public BaseState
{
public:
	State_Start();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	enum class EStartScreenMode
	{
		StartMenu,
		JobSelect
	};

	void ProcessStartMenu();
	void ProcessJobSelect();

private:
	EStartScreenMode CurrentMode = EStartScreenMode::StartMenu;
};
