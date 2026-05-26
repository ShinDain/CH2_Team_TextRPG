#include "pch.h"
#include "Object.h"
#include "Component.h"

Object::Object() : Name("None")
{
}

Object::Object(const std::string& InName)
	:Name(InName)
{
}

void Object::AddComponent(Component* InComp)
{
	if (InComp)
	{
		OwnedComponents.insert(InComp);
	}
}

void Object::RemoveComponent(Component* InComp)
{
	if (InComp)
	{
		OwnedComponents.erase(InComp);
	}
}
