#pragma once

#include "Combat/BattleSystem.h"
#include "Core/State.h"
#include "UI/BattleRenderer.h"

class State_Battle : public BaseState
{
public:
	State_Battle();
	~State_Battle() override;

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	void SetupRendererFromBattleSystem();
	void DrawBattleView();
	void DrawSkillInputPrompt();
	void ClearBattlePanelInputLine();
	void AddTurnLogs(const BattleTurnResult& Result);
	void PlayTurnResult(const BattleTurnResult& Result);

private:
	BattleSystem BattleSystemInst;
	BattleRenderer Renderer;
	bool bInitialized = false;
};
