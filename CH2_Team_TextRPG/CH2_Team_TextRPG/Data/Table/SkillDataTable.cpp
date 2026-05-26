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
	return nullptr;
}

const FSkillData* SkillDataTable::FindSkillDataByIndex(uint16_t Index) const
{
	return nullptr;
}

void SkillDataTable::ParseData(const json& InData)
{
}
