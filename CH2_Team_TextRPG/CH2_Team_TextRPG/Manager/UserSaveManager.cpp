#include "pch.h"
#include "UserSaveManager.h"

#include "Data/User/UserData.h"
#include "ObjectManager.h"
#include "Character/Component/InventoryComponent.h"
#include "Character/Component/SkillComponent.h"
#include "Character/Player/Player.h"
#include "Core/GameInstance.h"
#include "Data/Character/Stat.h"
#include "Data/DataLoader.h"
#include "Data/JsonDataParser.h"
#include "Data/Table/ScriptPathTable.h"
#include "Data/Table/SkillDataTable.h"
#include "Skill/Skill.h"

UserSaveManager::UserSaveManager()
{
	CachedUserData = std::make_unique<UserData>();
}

bool UserSaveManager::Save() const
{
	if (!CachedUserData)
	{
		GLog.AddLog("UserSaveManager -> 저장할 데이터가 없습니다.");
		return false;
	}

	try
	{
		json Json = *CachedUserData;
		JsonDataParser::Save(GetSavePath(), Json);
		return true;
	}
	catch (const json::exception& Exception)
	{
		GLog.AddLog(std::string("UserSaveManager -> 세이브 실패: ") + Exception.what());
		return false;
	}
}

bool UserSaveManager::Save(const UserData& InData)
{
	*CachedUserData = InData;
	bHasLoadedData = true;
	return Save();
}

bool UserSaveManager::SaveSnapShot()
{
	UpdateUserData();
	return Save();
}

bool UserSaveManager::Load()
{
	json Json;
	if (!JsonDataParser::Load(GetSavePath(), Json))
	{
		return false;
	}

	try
	{
		*CachedUserData = Json.get<UserData>();
		bHasLoadedData = true;
		return true;
	}
	catch (const json::exception& Exception)
	{
		GLog.AddLog(std::string("UserSaveManager-> Load 파싱 실패: ") + Exception.what());
		return false;
	}
}

UserData UserSaveManager::GetUserData() const
{
	UserData Ret;
	if (CachedUserData)
	{
		Ret = *CachedUserData;
	}
	return Ret;
}

bool UserSaveManager::HasLoadedData() const
{
	return bHasLoadedData;
}

void UserSaveManager::UpdateUserData()
{
	if (!CachedUserData) return;

	Player* FoundPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
	if (!FoundPlayer)
	{
		GLog.AddLog("UserSaveManager-> Player is null");
		return;
	}

	CachedUserData->Level = FoundPlayer->GetLevel();
	CachedUserData->Exp = FoundPlayer->GetExp();

	std::shared_ptr<InventoryComponent> Inventory = FoundPlayer->GetInventory();
	if (Inventory)
	{
		CachedUserData->Gold = Inventory->GetOwnedGold();

		CachedUserData->OwnedItems.clear();
		for (const FInventoryEntry& Entry : Inventory->GetItemList())
		{
			std::string NameId = std::to_string(Entry.Id);
			CachedUserData->OwnedItems[NameId] = Entry.Amount;
		}
	}

	std::shared_ptr<SkillComponent> SkillComp = FoundPlayer->FindComponent<SkillComponent>("Skill");
	if (SkillComp)
	{
		CachedUserData->Skills.clear();
		for (const class Skill* LearnedSkill : SkillComp->GetLearnedSkills())
		{
			if (LearnedSkill && LearnedSkill->GetSkillData())
			{
				CachedUserData->Skills.push_back(LearnedSkill->GetSkillData()->Idx);
			}
		}
	}
	
	const int CurrentMapNodeId = GameInstance::GetInstance().GetMapManager().GetCurrentNode()->Id;
	CachedUserData->MapIndex = CurrentMapNodeId;
}

std::string UserSaveManager::GetSavePath() const
{
	std::vector<std::string> Path = ScriptPathTable::GetInstance().GetFilePaths(Game::DataPaths::User);
	if (Path.empty())
	{
		assert(0 && "SavePath is empty");
		return "";
	}
	return Path.front();
}
