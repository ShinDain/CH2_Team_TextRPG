#pragma once
#include "DataTable.h"
#include "Enum/EEffect.h"
#include "Effect/EffectData.h"

struct FSkillData
{
	std::string Name;			// 스킬 명
	std::string Description;	// 스킬 설명

	uint16_t Idx;				// 스킬 Idx
	uint16_t ManaCost;			// MP 소모량

	ETargetType TargetType;				// 타겟 유형
	uint8_t Cooldown;					// 쿨타임
	uint8_t HitCount;					// 타격 횟수
	uint8_t Duration;					// 스킬 버프/디버프 지속 턴수 (없으면 0)
	std::vector<EffectData> Effects;	// 스킬 효과 목록
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FSkillData, Name, Description, Idx, ManaCost, TargetType, Cooldown, HitCount, Duration, Effects);

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
