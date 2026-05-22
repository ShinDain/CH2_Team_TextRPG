#include "pch.h"
#include "ObjectManager.h"

ObjectManager& ObjectManager::GetInstance()
{
	static ObjectManager Instance;
	return Instance;
}

ObjectManager::~ObjectManager()
{
	for (auto& pair : Objects)
	{
		delete pair.second;
		pair.second = nullptr;
	}

	Objects.clear();
}
