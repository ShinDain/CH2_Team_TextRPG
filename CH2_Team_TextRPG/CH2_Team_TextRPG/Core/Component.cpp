#include "pch.h"
#include "Component.h"

Component::Component(Object* InOwner, std::string InName)
	: Object(InName), Owner(InOwner)   // 베이스 먼저 (멤버 선언 순서와 맞춤)
{
	if (Owner) Owner->AddComponent(this);
}

Component::~Component()
{
	if (Owner) Owner->RemoveComponent(this);
}

bool Component::Initialize()
{
	return false;
}
