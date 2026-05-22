#include "pch.h"
#include "Object.h"

Object::Object() : Name("None")
{
}

Object::Object(const std::string& InName)
	:Name(InName)
{
}
