#pragma once
#include "Core/Component.h"
#include "Enum/EEffect.h"
#include <map>
#include <Data/Table/SkillDataTable.h>

class EffectComponent : public Component
{
public:
	EffectComponent() = delete;
	EffectComponent(Object* InOwner);
	~EffectComponent() override;

	//void ApplyEffect(const FSkillEffect& Effect);
	
	void UpdateEffects();

	void RemoveExpiredEffects();

	bool Initialize() override;

private:
	std::map<FSkillData, uint8_t> SkillDurations;
	
};