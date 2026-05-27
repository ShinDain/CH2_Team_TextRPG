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

void Object::AddComponent(const std::shared_ptr<Component>& InComp)
{
	if (InComp)
	{
		OwnedComponents.push_back(InComp);
	}
}

void Object::RemoveComponent(const std::shared_ptr<Component>& InComp)
{
	if (!InComp) return;
	auto It = std::find(OwnedComponents.begin(), OwnedComponents.end(), InComp);
	if (It != OwnedComponents.end())
	{
		OwnedComponents.erase(It);
	}
}
