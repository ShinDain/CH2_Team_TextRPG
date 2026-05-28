#include "pch.h"
#include "State_BattleEnd.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Manager/CombatManager.h"
#include "Manager/StateManager.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
State_BattleEnd::State_BattleEnd()
{
	Name = "BattleEnd";
}

State_BattleEnd::~State_BattleEnd()
{
}

void State_BattleEnd::Enter()
{
	Player* PlayerCharacter = GameInstance::GetInstance().GetMainPlayer();
	if (!PlayerCharacter) 
	{
		return;
	}
	std::vector<Monster*> AliveMonsters = CombatManager::GetInstance().GetAliveMonsters();
	if (AliveMonsters.empty() && !PlayerCharacter->IsDead())
	{
		int TotalExp = 0;
		int TotalGold = 0;

		std::vector<Monster*> AllMonsters = CombatManager::GetInstance().GetAllMonsters();
		for (Monster* MonsterChar : AllMonsters)
		{
			if (MonsterChar)
			{
				TotalExp += MonsterChar->GetExp();
				TotalGold += MonsterChar->GetDropGold();
			}
		}

		PlayerCharacter->AddExp(TotalExp);
		PlayerCharacter->ModifyGold(TotalGold);

		GLog.AddLog("[전투 승리] 모든 적을 쓰러뜨렸습니다!");
		GLog.AddLog("[보상] 획득 경험치: " + std::to_string(TotalExp) + " EXP");
		GLog.AddLog("[보상] 획득 골드: " + std::to_string(TotalGold) + " GOLD");
	}
	else if (PlayerCharacter->IsDead())
	{
		GLog.AddLog("[전투 패배] 플레이어가 사망했습니다...");
	}

	GLog.AddLog("아무 키나 누르면 다음 화면으로 이동합니다...");
}

void State_BattleEnd::Process()
{
	std::string Dummy;
	if (GInput >> Dummy)
	{
		Player* PlayerCharacter = GameInstance::GetInstance().GetMainPlayer();
		if (PlayerCharacter && PlayerCharacter->IsDead())
		{
			StateManager::GetInstance().ChangeState(EState::Result);
		}
		else
		{
			StateManager::GetInstance().ChangeState(EState::Map);
		}
	}
}

void State_BattleEnd::Exit()
{
	CombatManager::GetInstance().Clear();
}