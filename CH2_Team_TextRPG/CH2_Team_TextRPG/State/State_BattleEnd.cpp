#include "pch.h"
#include "State_BattleEnd.h"

#include "Character/Component/LevelComponent.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Manager/CombatManager.h"
#include "Manager/StateManager.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "Manager/ObjectManager.h"

State_BattleEnd::State_BattleEnd()
{
	Name = "BattleEnd";
}

State_BattleEnd::~State_BattleEnd()
{
}

void State_BattleEnd::Enter()
{
	Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
	assert(LoadPlayer && "LoadPlayer is null");


	std::shared_ptr<LevelComponent> LevelComp = LoadPlayer->FindComponent<LevelComponent>("Level");
	// std::bind()

	if (CombatManager::GetInstance().IsVictory())
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

		LoadPlayer->AddExp(TotalExp);
		LoadPlayer->ModifyGold(TotalGold);

		GLog.AddLog("[전투 승리] 모든 적을 쓰러뜨렸습니다!");
		GLog.AddLog("[보상] 획득 경험치: " + std::to_string(TotalExp) + " EXP");
		GLog.AddLog("[보상] 획득 골드: " + std::to_string(TotalGold) + " GOLD");
	}
	else
	{
		GLog.AddLog("[전투 패배] 플레이어가 사망했습니다...");
	}

}

void State_BattleEnd::Process()
{
	std::string Dummy;
	if (GInput >> Dummy)
	{
		Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
		assert(LoadPlayer && "LoadPlayer is null");
		

		const BattleStartData* StartData = GameInstance::GetInstance().GetBattleStartData();
		if (StartData && StartData->bIsBoss)
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