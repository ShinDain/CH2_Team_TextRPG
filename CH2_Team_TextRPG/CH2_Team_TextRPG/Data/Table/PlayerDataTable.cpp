#include "pch.h"
#include "PlayerDataTable.h"

PlayerDataTable& PlayerDataTable::GetInstance()
{
	static PlayerDataTable Instance;
	return Instance;
}

const PlayerBaseData* PlayerDataTable::FindById(int Index) const
{
	for (const PlayerBaseData& Data : PlayerDataContainer)
	{
		if (Data.Index == Index)
		{
			return &Data;
		}
	}
	return nullptr;
}

const PlayerBaseData* PlayerDataTable::FindByClassName(const std::string& ClassName) const
{
	for (const PlayerBaseData& Data : PlayerDataContainer)
	{
		if (Data.ClassName == ClassName)
		{
			return &Data;
		}
	}
	return nullptr;
}

void PlayerDataTable::ParseData(const json& InData)
{
	if (InData.empty())
	{
		GLog.PrintLogOnce("PlayerData is Empty.");
		return;
	}

	std::vector<PlayerBaseData> ParseDatas = InData.get<std::vector<PlayerBaseData>>();
	for (PlayerBaseData& Data : ParseDatas)
	{
		PlayerDataContainer.push_back(std::move(Data));
	}
}
