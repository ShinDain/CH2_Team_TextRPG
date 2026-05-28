#include "pch.h"
#include "Character/Player/CharacterCreator.h"
#include "Character/Player/Player.h"
#include "Character/Component/InventoryComponent.h"
#include "Core/GameInstance.h"
#include "Data/Character/Stat.h"
#include "Manager/LogManager.h"
#include "Map/MapManager.h"

bool CharacterCreator::CreatePlayerFromJob(GameInstance& Instance, const CharacterJobData& SelectedJob)
{
	LogManager& Log = Instance.GetLogManager();
	Player* MainPlayer = Instance.GetMainPlayer();

	if (MainPlayer == nullptr)
	{
		Log.AddLog("플레이어 정보를 찾을 수 없습니다.");
		return false;
	}

	ApplyCharacterStats(*MainPlayer, SelectedJob.Stats);

	std::shared_ptr<InventoryComponent> Inventory = MainPlayer->GetInventory();
	if (Inventory != nullptr)
	{
		Inventory->ResetInventory();
		// TODO: CharacterData.json에 StartGold 필드가 추가되면 이 임시값 대신 해당 값을 사용합니다.
		Inventory->SetGold(150);
	}

	MainPlayer->RestoreAll();
	Instance.GetMapManager().GenerateFixedMap();
	Log.AddLog(SelectedJob.JobName + " 캐릭터를 생성했습니다.");

	return true;
}

void CharacterCreator::ApplyCharacterStats(Player& MainPlayer, const CharacterStatsData& Stats)
{
	MainPlayer.SetBaseStat(EStatType::Health, Stats.Health);
	MainPlayer.SetBaseStat(EStatType::Mana, Stats.Mana);
	MainPlayer.SetBaseStat(EStatType::Attack, Stats.Attack);
	MainPlayer.SetBaseStat(EStatType::Defense, Stats.Defense);
	MainPlayer.SetBaseStat(EStatType::ActionSpeed, Stats.ActionSpeed);
}
