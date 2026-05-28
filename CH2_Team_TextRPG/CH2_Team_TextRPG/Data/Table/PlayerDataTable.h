#pragma once
#include "DataTable.h"
#include "Data/Character/Stat.h"

struct PlayerBaseData
{
	int Index = 0;
	std::string ClassName;
	std::string Description;
	std::map<std::string, int> InitialStats;
	std::vector<int> InitialSkills;
	std::vector<int> InitialItems;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerBaseData, Index, ClassName, Description, InitialStats, InitialSkills, InitialItems);

class PlayerDataTable : public BaseDataTable
{
public:
	static PlayerDataTable& GetInstance();

	const PlayerBaseData* FindById(int Index) const;
	const PlayerBaseData* FindByClassName(const std::string& ClassName) const;
	const std::vector<PlayerBaseData>& GetAll() const { return PlayerDataContainer; }

private:
	PlayerDataTable() = default;
	void ParseData(const json& InData) override;

private:
	std::vector<PlayerBaseData> PlayerDataContainer;
};
