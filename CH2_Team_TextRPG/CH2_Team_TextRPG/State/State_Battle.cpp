#include "pch.h"
#include "Combat/BattleUI.h"
#include "Combat/CombatCondition.h"
#include "Character/Component/EffectComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Component/InventoryComponent.h"
#include "Character/Player/Player.h"
#include "Character/Monster/Monster.h"
#include "Character/Monster/MonsterFactory.h"
#include "Data/Table/SkillDataTable.h"
#include "Data/Table/ItemDataTable.h"
#include "Manager/ObjectManager.h"
#include "Manager/CombatManager.h"
#include "State_Battle.h"

#include "Data/Table/MonsterDataTable.h"

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
	std::vector<Monster*> Monsters;
	
	for (const BattleMonsterStartData& data : StartData->Monsters)
	{
		const MonsterData* MonsData = MonsterDataTable::GetInstance().FindMonsterDataById(data.MonsterId);
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
	// TODO : 전투 종료 시 효과 제거 (버프/디버프 등)
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
		auto InventoryComp = PlayerCharacter->FindComponent<InventoryComponent>("Inventory");
		Skill* SelectedSkill = nullptr;
		int SelectedItemId = -1;

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
			SelectedItemId = BattleUI::ShowItemMenu(InventoryComp);
		}

		ETargetType TargetType = ETargetType::SINGLE_ENEMY;
		if (SelectedSkill)
		{
			TargetType = SelectedSkill->GetSkillData()->TargetType;
		}
		else if (SelectedItemId > 0)
		{
			const FConsumableItemData* ConsumableData = ConsumableDataTable::GetInstance().FindConsumableDataByIndex(SelectedItemId);
			if (ConsumableData)
			{
				TargetType = ConsumableData->TargetType;
			}
		}
		else
		{
			continue;
		}

		vector<Object*> Targets;
		vector<Object*> SelectableTargets;
		int TargetCount = 1;

		if (TargetType == ETargetType::SELF || TargetType == ETargetType::SINGLE_ALLY || TargetType == ETargetType::ALL_ALLIES)
		{
			SelectableTargets.push_back(PlayerCharacter);
			TargetCount = (TargetType == ETargetType::ALL_ALLIES) ? SelectableTargets.size() : 1;
		}
		else
		{
			for (Monster* m : AliveMonsters)
			{
				SelectableTargets.push_back(m);
			}
			TargetCount = (TargetType == ETargetType::ALL_ENEMIES) ? AliveMonsters.size() : 1;
		}
		Targets = BattleUI::ShowTargetMenu(SelectableTargets, TargetCount);
		
		if (!Targets.empty())
		{
			if (SelectedSkill)
			{
				CombatManager::GetInstance().ExecuteSkill(PlayerCharacter, Targets, SelectedSkill);
			}
			else if (SelectedItemId > 0 && InventoryComp)
			{
				CombatManager::GetInstance().ExecuteItem(PlayerCharacter, Targets, SelectedItemId);
			}
			BattleUI::PlayHitAnimation(Targets);
			BattleUI::DrawBattleView(AliveMonsters);
			bTurnEnded = true;
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