#include "pch.h"
#include "State_Start.h"

#include "Character/Component/InventoryComponent.h"
#include "Character/Component/LevelComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Player/Player.h"
#include "Combat/CombatCondition.h"
#include "Core/GameInstance.h"
#include "Data/Table/PlayerDataTable.h"
#include "Data/User/UserData.h"
#include "Manager/InputManager.h"
#include "Manager/ObjectManager.h"
#include "Manager/StateManager.h"
#include "Manager/UserSaveManager.h"
#include "UI/PlayerSetupScreen.h"
#include "UI/StartMenuScreen.h"

State_Start::State_Start()
{
	Name = "Start";
}

void State_Start::Enter()
{
	GLog.AddLog("시작 메뉴에 진입했습니다.");
}

void State_Start::Process()
{
	GameInstance& Instance = GameInstance::GetInstance();

	StartMenuScreen::DrawStartMenu();

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		GLog.AddLog("메뉴 번호를 다시 선택해주세요.");
		return;
	}

	switch (Input)
	{
		case 1:
		{
			NewPlayer();
			AddTransition<AlwaysTrueCondition>(EState::Map);
			break;
		}
		case 2:
		{
			LoadPlayer();
			AddTransition<AlwaysTrueCondition>(EState::Map);
			break;
		}
		case 0:
		{
			Instance.Quit();
			break;
		}
		default:
			Instance.GetLogManager().AddLog("메뉴 번호를 다시 선택해주세요.");
			break;
	}
}

void State_Start::Exit()
{
}

void State_Start::NewPlayer()
{
	UserData Data;
	while (1)
	{
		PlayerSetupScreen::DrawPlayerNameInput();
		if (!(GInput >> Data.UserName))
		{
			PlayerSetupScreen::DrawPlayerNameError();
			continue;
		}
		break;
	}
	
	Player* NewPlayer = ObjectManager::GetInstance().CreateObject<Player>();
	NewPlayer->SetDisplayName(Data.UserName);
	if (!NewPlayer)
	{
		GLog.AddLog("플레이어 생성에 실패했습니다.");
		return;
	}

	PlayerSetupScreen::DrawPlayerJobSelect();

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		GLog.AddLog("잘못된 입력입니다.");
		return;
	}

	if (Input == 0)
	{
		AddTransition<AlwaysTrueCondition>(EState::Start);
		return;
	}

	if (Input >= 1 && Input <= 3)
	{
		const PlayerBaseData* PlayerInfo = PlayerDataTable::GetInstance().FindById(Input);
		if (PlayerInfo)
		{
			for (auto& It : PlayerInfo->InitialStats)
			{
				NewPlayer->SetBaseStat(StringToEStatType(It.first), It.second);
			}
			Data.ClassIndex = Input;
			GSharedSaveMgr->Save(Data);
			GSharedSaveMgr->SaveSnapShot();
			
			GLog.AddLog("새 게임을 시작합니다: " + Data.UserName);
			return;
		}
		GLog.AddLog("직업 데이터를 찾을 수 없습니다.");
		return;
	}
	
	GLog.AddLog("직업 번호를 다시 선택해주세요.");
}

void State_Start::LoadPlayer()
{
	if (!GSharedSaveMgr->Load())
	{
		GLog.AddLog("저장된 데이터가 없거나 손상되었습니다.");
		return;
	}

	const UserData Loaded = GSharedSaveMgr->GetUserData();

	Player* LoadedPlayer = ObjectManager::GetInstance().CreateObject<Player>();
	if (!LoadedPlayer)
	{
		GLog.AddLog("플레이어 생성에 실패했습니다.");
		return;
	}
	LoadedPlayer->SetDisplayName(Loaded.UserName);

	const PlayerBaseData* PlayerInfo = PlayerDataTable::GetInstance().FindById(Loaded.ClassIndex);
	if (PlayerInfo)
	{
		for (auto& It : PlayerInfo->InitialStats)
		{
			LoadedPlayer->SetBaseStat(StringToEStatType(It.first) , It.second);
		}

		if (std::shared_ptr<LevelComponent> LevelComp =
			LoadedPlayer->FindComponent<LevelComponent>("Level"))
		{
			LevelComp->ReviveLevel(Loaded.Level);
		}
	}
	else
	{
		GLog.AddLog("저장된 직업 정보를 찾을 수 없습니다.");
	}

	if (std::shared_ptr<InventoryComponent> Inventory = LoadedPlayer->GetInventory())
	{
		Inventory->SetGold(Loaded.Gold);
		for (const auto& Pair : Loaded.OwnedItems)
		{
			try
			{
				const int ItemId = std::stoi(Pair.first);
				Inventory->AcquireItem(ItemId, Pair.second);
			}
			catch (const std::exception&)
			{
				GLog.AddLog("OwnedItems 키 변환 실패: " + Pair.first);
			}
		}
		for (const auto& Pair : Loaded.EquippedItems)
		{
			Inventory->Equip(Pair.second);
		}
	}

	if (std::shared_ptr<SkillComponent> SkillComp = LoadedPlayer->FindComponent<SkillComponent>("Skill"))
	{
		for (uint16_t SkillId : Loaded.Skills)
		{
			SkillComp->AddSkill(SkillId);
		}
	}
	
	if (std::shared_ptr<LevelComponent> LevelComp = LoadedPlayer->FindComponent<LevelComponent>("Level"))
	{
		LevelComp->SetExp(Loaded.Exp);
	}
	
	GameInstance::GetInstance().GetMapManager().SetCurrentNodeId(Loaded.MapIndex);
	
	GLog.AddLog("저장된 게임을 불러왔습니다: " + Loaded.UserName);
}
