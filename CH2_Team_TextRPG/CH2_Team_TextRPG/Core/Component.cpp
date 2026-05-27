#include "pch.h"
#include "Component.h"

Component::Component(Object* InOwner, std::string InName)
	: Object(InName), Owner(InOwner)
{
}

bool Component::Initialize()
{
	return false;
}
