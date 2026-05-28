#include "pch.h"
#include "State_BattleEnd.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Manager/CombatManager.h"
#include "Manager/StateManager.h"
#include "Core/GameInstance.h"

State_BattleEnd::State_BattleEnd()
{
	Name = "BattleEnd";
	AddTransition<AnyKeyPressCondition>(EState::Map);
}

State_BattleEnd::~State_BattleEnd()
{
}

void State_BattleEnd::Enter()
{
}

void State_BattleEnd::Process()
{
}

void State_BattleEnd::Exit()
{
}