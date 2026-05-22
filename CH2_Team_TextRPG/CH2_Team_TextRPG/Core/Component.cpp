#include "pch.h"
#include "Component.h"

Component::Component(Object* owner, std::string name)
	:Owner(owner), Object(name)
{
}

Component::~Component()
{
}
