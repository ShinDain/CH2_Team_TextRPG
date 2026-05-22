#pragma once
#include "Core/Object.h"

class ObjectManager
{
private:
	ObjectManager() {};
public:
	~ObjectManager();
	static ObjectManager& GetInstance();

	template<typename T, typename... Args>
	T* CreateObject(Args&&... args);

private:
	std::vector<Object*> Objects;
};

template<typename T, typename... Args>
inline T* ObjectManager::CreateObject(Args&&... args)
{
	T* newObject = new T(std::forward<Args>(args)...);

	Objects.push_back(newObject);
	if (newObject)
	{
		newObject->Initialize();
	}

	return newObject;
}
