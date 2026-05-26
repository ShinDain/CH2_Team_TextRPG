#pragma once
#include "DataTable.h"
#include "Enum/EEffect.h"
#include "Effect/EffectData.h"

// 스킬의 개별 '효과' 데이터
// struct FSkillEffect
// {
// 	EEffectType EffectType;		// 효과 유형 (공격, 회복, 버프, 디버프 등)
// 	int BaseValue;				// 고정 수치 (예: 고정 데미지 +10)
// 	uint32_t Multiplier;		// 스킬 배율 (예: 공격력의 150% -> 15000, 배율 계산 시 10000으로 나눔)
// 	uint8_t SuccessRate;		// 효과 적중 확률 (0~100)
// 	uint8_t DurationTurns : 3;	// 버프/디버프 유지 턴 수 (즉발 효과면 0)
// 	uint8_t Padding : 5;          
// };


struct FSkillData
{
	std::string Name;			// 스킬 명
	std::string Description;	// 스킬 설명

	uint16_t Idx;				// 스킬 Idx
	uint16_t ManaCost;			// MP 소모량

	ETargetType TargetType : 3;			// 타겟 유형
	uint8_t Cooldown : 3;				// 쿨타임
	uint8_t Padding : 2;
	
	std::vector<EffectData> Effects;	// 스킬 효과 목록
};

//NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FSkillData, Name, Description, Idx, ManaCost, TargetType, Cooldown, EffectDatas);

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
