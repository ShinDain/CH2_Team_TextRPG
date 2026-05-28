#pragma once
#include "Core/Component.h"
#include "Enum/EEffect.h"
#include <vector>

class Effect;
class Object;


enum class EActiveEffectType
{
	OverTime, // 1. 매 턴마다 효과가 발동하는 류 (독, 화상 등 도트 대미지/힐)
	Modifier, // 2. 시작 시 1회 적용 후 지속시간 동안 유지되는 류 (스탯 버프/디버프)
	State     // 3. 실제 수치 적용 없이 상태만 등록/유지되는 류 (기절, 무적)
};

struct FActiveEffect
{
	Effect* EffectPtr;          // 적용될 효과 객체
	Object* Caster;             // 효과를 시전한 객체
	int RemainingDuration;      // 남은 턴 수
	EActiveEffectType Type;     // 효과 동작 방식
};

class EffectComponent : public Component
{
public:
	EffectComponent() = delete;
	EffectComponent(Object* InOwner);
	~EffectComponent() override;

	
	void AddActiveEffect(Effect* InEffect, Object* InCaster, int InDuration);
	
	bool HasActiveEffect(Effect* InEffect) const;
	bool HasEffectByTag(const std::string& InTag) const;

	void UpdateEffects();

	void RemoveExpiredEffects();

	bool Initialize() override;

private:
	EActiveEffectType DetermineEffectType(const std::string& InTag) const;

private:
	std::vector<FActiveEffect> ActiveEffects;
	
};