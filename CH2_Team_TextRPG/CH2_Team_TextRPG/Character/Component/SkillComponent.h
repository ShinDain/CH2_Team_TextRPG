#pragma once
#include "Core/Component.h"
#include "Skill/Skill.h"
#include <vector>
#include <map>

class SkillComponent : public Component
{
public:
	SkillComponent(Object* InOwner);
	virtual ~SkillComponent();

	virtual bool Initialize() override;

	/**
	* @brief 캐릭터에게 새로운 스킬을 가르칩니다.
	* @param SkillId 가르칠 스킬의 ID
	*/ 
	void AddSkill(uint16_t SkillId);

	/**
	* @brief 보유한 스킬 객체 목록을 반환합니다.
	* @return 보유한 스킬 객체 목록
	*/
	const std::vector<Skill*>& GetLearnedSkills() const { return LearnedSkills; };

	/**
	* @brief 매 턴 시작 시 쿨타임을 1씩 감소시킵니다.
	*/
	void UpdateCooldowns();

	/**
	* @brief 스킬 사용 가능 여부 (쿨타임이 0 이하인지) 확인합니다.
	* @param SkillId 확인할 스킬의 ID
	* @return 스킬 사용 가능 여부
	*/
	bool IsSkillReady(uint16_t SkillId) const;

	/**
	* @brief 스킬 사용 시 쿨타임을 적용합니다.
	*/
	void ApplyCooldown(uint16_t SkillId);
	void ApplyCooldown(const Skill* InSkill);

	/**
	* @brief 스킬 사용 시 비용을 소모할 수 있는지 확인합니다.
	* @param SkillId 소모할 스킬의 ID
	* @return 비용 소모 성공 여부
	*/
	bool CheckCost(uint16_t SkillId);

	/**
	* @brief 스킬 사용 시 비용을 소모합니다.
	* @param SkillId 소모할 스킬의 ID
	* @return 비용 소모 성공 여부
	*/
	bool ConsumeCost(uint16_t SkillId);
	bool ConsumeCost(const Skill* InSkill);

private:
	/**
	* @brief 스킬 ID에 해당하는 스킬 객체를 찾습니다.
	* @param SkillId 찾을 스킬의 ID
	* @return 해당 스킬 객체 포인터 (찾지 못한 경우 nullptr)
	*/
	Skill* FindSkillById(uint16_t SkillId) const;

private:
	// 사용가능한 스킬 객체 목록
	std::vector<Skill*> LearnedSkills; 
};