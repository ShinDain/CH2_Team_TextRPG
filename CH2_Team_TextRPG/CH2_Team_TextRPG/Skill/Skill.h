#pragma once

#include "Data/Table/SkillDataTable.h"

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

	const FSkillData* GetSkillData() { return Data; }
	std::vector<Effect*> GetEffects() { return Effects; }
private:
	const FSkillData* Data;
	std::vector<Effect*> Effects;
};

