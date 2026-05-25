#include "pch.h"
#include "SkillDataTable.h"

SkillDataTable::~SkillDataTable()
{
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
