#include "pch.h"
#include "ObjectManager.h"

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager Instance;
	return Instance;
}

ObjectManager::~ObjectManager()
{
	for (Object* object : Objects)
	{
		delete object;
	}

	Objects.clear();
}
