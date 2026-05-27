#include "pch.h"
#include "LevelDataTable.h"

LevelDataTable::LevelDataTable() :
   MaxLevel(1)
{
#if DEBUG_CODE
	nlohmann::json j = nlohmann::json::parse(R"([
  {
    "Level": 2, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 220 },
      { "Type": "Attack", "Value": 35  }
    ]
  },
  {
    "Level": 3, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 260 },
      { "Type": "Attack", "Value": 45  }
    ]
  },
  {
    "Level": 4, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 320 },
      { "Type": "Attack", "Value": 60  }
    ]
  },
  {
    "Level": 5, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 400 },
      { "Type": "Attack", "Value": 80  }
    ]
  },
  {
    "Level": 6, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 500 },
      { "Type": "Attack", "Value": 105 }
    ]
  },
  {
    "Level": 7, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 620 },
      { "Type": "Attack", "Value": 135 }
    ]
  },
  {
    "Level": 8, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 760 },
      { "Type": "Attack", "Value": 170 }
    ]
  },
  {
    "Level": 9, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 920 },
      { "Type": "Attack", "Value": 210 }
    ]
  },
  {
    "Level": 10, "Exp": 100,
    "Stats": [
      { "Type": "Health", "Value": 1100 },
      { "Type": "Attack", "Value": 255  }
    ]
  }
])");

	  std::vector<LevelData> ParseDatas = j.get<std::vector<LevelData>>();
	  for (auto& It : ParseDatas)
	  {
	      MaxLevel = std::max(MaxLevel, It.Level);
		    LevelDataContainer.emplace(It.Level, std::move(It));
	  }
#endif
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
