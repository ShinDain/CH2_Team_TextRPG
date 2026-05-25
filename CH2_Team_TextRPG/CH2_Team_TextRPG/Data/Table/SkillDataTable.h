#pragma once
#include "DataTable.h"

enum class ESkillRange : uint8_t { Single = 0, Area = 1 };
enum class ESkillType : uint8_t { Attack = 0, Heal = 1, Buff = 2, Debuff = 3 };

struct FSkillData
{
	std::string Name;			// 스킬 명
	std::string Description;	// 스킬 설명

	uint16_t Idx;				// 스킬 Idx
	uint16_t ManaCost;          // MP 소모량
	union {
		int16_t SkillPower;			// 스킬 위력 (공격/회복 전용 값)
		int16_t BuffDebuffValue;	// 버프/디버프 전용 값
	};

	uint8_t Duration  : 4;			// 스킬 지속시간
	uint8_t Cooldown  : 4;			// 쿨타임
	ESkillRange Range : 1;			// 스킬 범위 (단일, 범위)
	ESkillType  Type  : 2;			// 스킬 종류 (공격, 회복, 버프, 디버프)
	uint8_t Padding   : 5;		
};


class SkillDataTable final : public BaseDataTable
{
private:
	SkillDataTable() {};
public:
	~SkillDataTable();

	static SkillDataTable& GetInstance();

	const FSkillData* FindSkillDataByName(const std::string& Name) const;
	const FSkillData* FindSkillDataByIndex(uint16_t Index) const;

protected:
	virtual void ParseData(const json& InData) override;

private:
	std::vector<const FSkillData*> SkillDatas;

	std::unordered_map<std::string, const FSkillData*> NameMap;
	std::unordered_map<uint16_t, const FSkillData*> IndexMap;
};

