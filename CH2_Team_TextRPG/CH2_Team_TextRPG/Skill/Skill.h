#pragma once

struct FSkillData;
class Object;
class Effect;

class Skill
{
public:
	Skill() = delete;
	Skill(const FSkillData* InData);
	virtual ~Skill();

	virtual void Active(Object* Instigator, std::vector<Object*> Targets);
	virtual void AddEffect(Effect* InEffect);

	void UpdateCooldown();
	void ApplyCooldown();
	bool IsReady() const;
	uint8_t GetCurrentCooldown() const { return CurrentCooldown; }

	const FSkillData* GetSkillData() const { return Data; }
	std::vector<Effect*> GetEffects() const { return Effects; }
private:
	const FSkillData* Data;
	std::vector<Effect*> Effects;
	uint8_t CurrentCooldown = 0;
};
