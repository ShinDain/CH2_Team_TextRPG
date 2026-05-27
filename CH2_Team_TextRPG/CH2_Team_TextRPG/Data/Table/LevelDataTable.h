#pragma once
#include "DataTable.h"
#include "Data/Character/Stat.h"

struct StatValue
{
	EStatType Type = EStatType::Max;
	int Value = 0;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(StatValue, Type, Value);

struct LevelData
{
	LevelData() = default;

	int Level = 0;
	int Exp = 0;
	std::vector<StatValue> Stats;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LevelData, Level, Exp, Stats);

class LevelDataTable : public BaseDataTable
{
public:
	static LevelDataTable& GetInstance();

	const LevelData* FindByLevel(int Level) const;
	int GetMaxLevel() const { return MaxLevel; }

protected:
	void ParseData(const json& InData) override;

private:
	LevelDataTable();

private:
	std::map<int, LevelData> LevelDataContainer;
	int MaxLevel;
};
