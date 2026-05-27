#pragma once
#include "Effect/Effect.h"

class Effect_Poison : public Effect
{
public:
	Effect_Poison(int InValue);

	virtual void Apply(Object* Instigator, std::vector<Object*> Targets) override;
	virtual void Remove(Object* Instigator, std::vector<Object*> Targets) override;

private:
	int Duration; 
};
