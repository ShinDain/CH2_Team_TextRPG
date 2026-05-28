#pragma once
#include "Effect/Effect.h"
#include <map>

class Effect_Debuff_Weakness : public Effect
{
public:
	Effect_Debuff_Weakness(int InValue);

	void Apply(Object* Instigator, std::vector<class Object*> Targets) override;
	void Remove(Object* Instigator, std::vector<class Object*> Targets) override;

private:
	std::map<class Object*, int> AppliedValues;
};