#pragma once
#include "Core/Component.h"
#include "Enum/EEffect.h"
#include <vector>

class Effect;
class Object;

struct FActiveEffect
{
	Effect* EffectPtr;          // 적용될 효과 객체
	Object* Caster;             // 효과를 시전한 객체
	int RemainingDuration;      // 남은 턴 수
};

class EffectComponent : public Component
{
public:
	EffectComponent() = delete;
	EffectComponent(Object* InOwner);
	~EffectComponent() override;

	
	void AddActiveEffect(Effect* InEffect, Object* InCaster, int InDuration);
	
	bool HasActiveEffect(Effect* InEffect) const;

	void UpdateEffects();

	void RemoveExpiredEffects();

	bool Initialize() override;

private:
	std::vector<FActiveEffect> ActiveEffects;
	
};