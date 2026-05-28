#include "pch.h"
#include "SkillDataTable.h"

SkillDataTable::~SkillDataTable()
{
	for (auto& data : SkillDatas)
	{
		delete data;
	}

	NameMap.clear();
	IndexMap.clear();
}

SkillDataTable& SkillDataTable::GetInstance()
{
	static SkillDataTable Instance;
	return Instance;
}

const FSkillData* SkillDataTable::FindSkillDataByName(const std::string& Name) const
{
	if (NameMap.find(Name) != NameMap.end())
	{
		return NameMap.at(Name);
	}
	return nullptr;
}

const FSkillData* SkillDataTable::FindSkillDataByIndex(uint16_t Index) const
{
	if (IndexMap.find(Index) != IndexMap.end())
	{
		return IndexMap.at(Index);
	}
	return nullptr;
}

void SkillDataTable::ParseData(const json& InData)
{
	for (const json& data : InData)
	{
		FSkillData* newData = new FSkillData();
		*newData = data;
		if (newData)
		{
			SkillDatas.emplace_back(newData);
			NameMap[newData->Name] = newData;
			IndexMap[newData->Idx] = newData;
		}
	}
}
