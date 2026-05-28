#pragma once
#include "Effect/Effect.h"

class Effect_Debuff_Burn : public Effect
{
public:
	Effect_Debuff_Burn(int InValue);

	void Apply(Object* Instigator, std::vector<class Object*> Targets) override;
	void Remove(Object* Instigator, std::vector<class Object*> Targets) override;
};