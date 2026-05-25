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

	virtual void Apply(class Object* Target) = 0;

	virtual std::string GetTag() { return Tag; }
private:
	std::string Tag;
};
