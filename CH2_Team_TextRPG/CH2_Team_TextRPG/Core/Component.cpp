#include "pch.h"
#include "Component.h"

Component::Component(Object* InOwner, std::string InName)
	:Owner(InOwner), Object(InName)
{
}

Component::~Component()
{
}
