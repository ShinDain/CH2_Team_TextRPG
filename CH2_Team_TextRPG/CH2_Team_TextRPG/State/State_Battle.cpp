#include "pch.h"
#include "Combat/BattleUI.h"
#include "Combat/CombatCondition.h"
#include "Character/Component/EffectComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Character/Monster/MonsterFactory.h"
#include "Data/Table/SkillDataTable.h"
#include "Data/Table/ItemDataTable.h"
#include "Manager/ObjectManager.h"
#include "Manager/CombatManager.h"
#include "State_Battle.h"

using namespace std;

State_Battle::State_Battle()
{
	Name = "Battle";

	AddTransition<CombatVictoryCondition>(EState::CombatEnd);
	AddTransition<CombatDefeatCondition>(EState::Result);
}

State_Battle::~State_Battle()
{
}

void State_Battle::Enter()
{
	Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
	assert(LoadPlayer && "LoadPlayer is null");

	const BattleStartData* StartData = GameInstance::GetInstance().GetBattleStartData();
	
	vector<Monster*> Monsters;
	for (const BattleMonsterStartData& data : StartData->Monsters)
	{
		Monster* NewMonster = MonsterFactory::CreateForPlayer(data.Name, LoadPlayer);
		if (NewMonster)
		{
			Monsters.emplace_back(NewMonster);
		}
	}
	CombatManager::GetInstance().Initialize(LoadPlayer, Monsters);
}

void State_Battle::Process()
{
	if (CombatManager::GetInstance().IsBattleEnd())
	{
		return;
	}

	Object* CurTurnCharacter = CombatManager::GetInstance().GetNextTurnCharacter();
	if (!CurTurnCharacter) return;
	
	auto EffectComp = CurTurnCharacter->FindComponent<EffectComponent>("Effect");
	bool bIsStunned = false;
	if (EffectComp)
	{
		bIsStunned = EffectComp->HasEffectByTag("State_Stun");
		EffectComp->UpdateEffects();
		EffectComp->RemoveExpiredEffects();
	}

	auto SkillComp = CurTurnCharacter->FindComponent<SkillComponent>("Skill");
	if (SkillComp)
	{
		SkillComp->UpdateCooldowns();
	}

	if (Player* PlayerChar = dynamic_cast<Player*>(CurTurnCharacter))
	{
		if (PlayerChar->IsDead()) return;
		if (bIsStunned)
		{
			GLog.AddLog("[상태이상] " + PlayerChar->GetName() + "은(는) 기절하여 턴을 넘깁니다.");
			return;
		}
		HandlePlayerTurn(PlayerChar);
	}
	else if (Monster* MonsterChar = dynamic_cast<Monster*>(CurTurnCharacter))
	{
		if (MonsterChar->IsDead()) return;
		if (bIsStunned)
		{
			GLog.AddLog("[상태이상] " + MonsterChar->GetName() + "은(는) 기절하여 턴을 넘깁니다.");
			return;
		}
		HandleMonsterTurn(MonsterChar);
	}
}

void State_Battle::Exit()
{
	BattleEnd(); // 전투 종료 보상 처리 및 로그 출력

	CombatManager::GetInstance().Clear();
}


void State_Battle::HandlePlayerTurn(Player* PlayerCharacter)
{
	bool bTurnEnded = false;
	while (!bTurnEnded)
	{
		std::vector<Monster*> AliveMonsters = CombatManager::GetInstance().GetAliveMonsters();
		BattleUI::DrawBattleView(AliveMonsters);

		EActionType Action = BattleUI::ShowActionMenu();
		auto SkillComp = PlayerCharacter->FindComponent<SkillComponent>("Skill");

		Skill* SelectedSkill = nullptr;

		if (Action == EActionType::ATTACK)
		{
			if (SkillComp && !SkillComp->GetLearnedSkills().empty())
			{
				SelectedSkill = SkillComp->GetLearnedSkills()[0];
			}
		}
		else if (Action == EActionType::SKILL)
		{
			SelectedSkill = BattleUI::ShowSkillMenu(SkillComp);
		}
		else if (Action == EActionType::ITEM)
		{
			GInput << "아이템 기능은 아직 구현되지 않았습니다.\n";
		}

		if (SelectedSkill)
		{
			int TargetCount = (SelectedSkill->GetSkillData()->TargetType == ETargetType::ALL_ENEMIES) ? AliveMonsters.size() : 1;
			vector<Object*> Targets = BattleUI::ShowTargetMenu(AliveMonsters, TargetCount);
			
			if (!Targets.empty())
			{
				CombatManager::GetInstance().ExecuteSkill(PlayerCharacter, Targets, SelectedSkill);
				BattleUI::PlayHitAnimation(Targets);
				BattleUI::DrawBattleView(AliveMonsters);
				bTurnEnded = true;
			}
		}
	}
}

void State_Battle::HandleMonsterTurn(Monster* MonsterCharacter)
{
	auto SkillComp = MonsterCharacter->FindComponent<SkillComponent>("Skill");
	if (SkillComp && !SkillComp->GetLearnedSkills().empty())
	{
		Skill* BasicAttack = SkillComp->GetLearnedSkills()[0];

		Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
		assert(LoadPlayer && "LoadPlayer is null");
		
		if (LoadPlayer && !LoadPlayer->IsDead())
		{
			std::vector<Object*> Targets = { LoadPlayer };
			
			// 몬스터 공격 애니메이션 재생
			BattleUI::PlayAttackAnimation(MonsterCharacter);
			CombatManager::GetInstance().ExecuteSkill(MonsterCharacter, Targets, BasicAttack);
			
			BattleUI::DrawBattleView(CombatManager::GetInstance().GetAliveMonsters());
		}
	}
}

void State_Battle::BattleEnd()
{
	// 전투 종료 후 보상 획득, 경험치 획득 등 처리

	Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
	assert(LoadPlayer && "Player Not Found");
	
	const BattleStartData* StartData = GameInstance::GetInstance().GetBattleStartData();

	if (!LoadPlayer || !StartData) {
		return;
	}
	// 승리 조건 검사: 살아있는 몬스터가 없고 플레이어가 생존해 있는가?
	std::vector<Monster*> AliveMonsters = CombatManager::GetInstance().GetAliveMonsters();
	if (AliveMonsters.empty() && !LoadPlayer->IsDead())
	{
		int TotalExp = 0;
		int TotalGold = 0;

		// 이번 전투에 참여했던 몬스터 데이터 스캔
		for (const BattleMonsterStartData& data : StartData->Monsters)
		{
			// 💡 [참고] 프로젝트의 BattleMonsterStartData 구조체 안에 정의된 
			// 경험치(Exp)와 골드(Gold) 변수명으로 매칭해 주세요!
			TotalExp += 100;//data.Exp;
			TotalGold += 100;//data.Gold;
		}

		LoadPlayer->AddExp(TotalExp);
		LoadPlayer->ModifyGold(TotalGold);
	
		GLog.AddLog("[전투 승리] 모든 적을 쓰러뜨렸습니다!");
		GLog.AddLog("[보상] 획득 경험치: " + to_string(TotalExp) + " EXP");
		GLog.AddLog("[보상] 획득 골드: " + to_string(TotalGold) + " GOLD");
	}
	
}