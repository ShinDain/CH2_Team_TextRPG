#include "pch.h"
#include "LevelDataTable.h"

LevelDataTable::LevelDataTable() :
   MaxLevel(1)
{
}

LevelDataTable& LevelDataTable::GetInstance()
{
	  static LevelDataTable Instance;
	  return Instance;
}

const LevelData* LevelDataTable::FindByLevel(int Level) const
{
	  auto Found = LevelDataContainer.find(Level);
	  if (Found != LevelDataContainer.end())
	  {
		    return &Found->second;
	  }
	  return nullptr;
}

void LevelDataTable::ParseData(const json& InData)
{
	  std::vector<LevelData> ParseDatas = InData.get<std::vector<LevelData>>();
	  for (auto& It : ParseDatas)
	  {
		    MaxLevel = std::max(MaxLevel, It.Level);
		    LevelDataContainer.emplace(It.Level, std::move(It));
	  }
}
