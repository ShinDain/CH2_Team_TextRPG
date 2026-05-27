#pragma once
#include "Effect/EffectTag.h"

class Effect
{
public:
	Effect() = delete;
	Effect(const Effect& rhs) = delete;
	Effect operator=(const Effect& rhs) = delete;
	Effect(const std::string& Tag, int InValue);
	virtual ~Effect();

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) = 0;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) = 0;

	std::string GetTag() const { return Tag; }
	int GetValue() const { return Value; }
protected:
	std::string Tag;
	int Value;
};
