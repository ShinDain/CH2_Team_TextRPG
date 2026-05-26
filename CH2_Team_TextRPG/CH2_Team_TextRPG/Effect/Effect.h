#pragma once
#include "Effect/EffectTag.h"

class Effect
{
public:
	Effect() = delete;
	Effect(const Effect& rhs) = delete;
	Effect operator=(const Effect& rhs) = delete;
	Effect(const std::string& Tag);
	virtual ~Effect();

	virtual void Apply(class Object* Instigator, std::vector<class Object*> Targets) = 0;
	virtual void Remove(class Object* Instigator, std::vector<class Object*> Targets) = 0;

	virtual std::string GetTag() { return Tag; }
private:
	std::string Tag;
};
