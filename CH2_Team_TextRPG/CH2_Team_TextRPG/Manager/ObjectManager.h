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

	template<typename T>
	T* FindObject(const std::string& Name);

	template<typename T>
	void AddObject(T* InObject);

	template<typename T>
	void RemoveObject(T* InObject);

private:
	std::unordered_map<std::string, Object*> Objects;
};

template<typename T, typename... Args>
inline T* ObjectManager::CreateObject(Args&&... args)
{
	T* newObject = new T(std::forward<Args>(args)...);

	std::string objectName = newObject->GetName();
	Objects.emplace(objectName, newObject);
	if (newObject)
	{
		newObject->Initialize();
	}

	return newObject;
}

template<typename T>
inline T* ObjectManager::FindObject(const std::string& Name)
{
	T* result = nullptr;
	auto iter = Objects.find(Name);
	if (iter != Objects.end())
	{
		result = dynamic_cast<T*>(iter->second);
	}

	return result;
}

template<typename T>
inline void ObjectManager::AddObject(T* InObject)
{
	if (InObject == nullptr)
		return;

	Objects.emplace(InObject->GetName(), InObject);
}

template<typename T>
inline void ObjectManager::RemoveObject(T* InObject)
{
	if (InObject == nullptr)
		return;

	for (auto it = Objects.begin(); it != Objects.end(); ++it)
	{
		if (it->second == InObject)
		{
			Objects.erase(it);
			break;
		}
	}

	delete InObject;
}

template<typename T, typename... Args>
inline T* CreateObject(Args&&... args)
{
	return ObjectManager::GetInstance().CreateObject<T>(std::forward<Args>(args)...);
}

template<typename T>
inline T* FindObject(const std::string& Name)
{
	return ObjectManager::GetInstance().FindObject<T>(Name);
}

template<typename T>
inline void AddObject(T* InObject)
{
	ObjectManager::GetInstance().AddObject<T>(InObject);
}

template<typename T>
inline void RemoveObject(T* InObject)
{
	ObjectManager::GetInstance().RemoveObject<T>(InObject);
}