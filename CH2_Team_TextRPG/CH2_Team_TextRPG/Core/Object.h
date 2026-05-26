#pragma once

class Component;

class Object
{
public:
	Object();
	Object(const std::string& InName);

	const std::string& GetName() const { return Name; }
	
	virtual bool Initialize() = 0;

	void AddComponent(Component* InComp);
	void RemoveComponent(Component* InComp);

	template <typename T>
	T* FindComponent(const std::string& ComponentName) const;
	
	template <typename T, typename... Arguments>
	T* AddComponent(Arguments&&... Args);

protected:
	std::string Name;

private:
	std::unordered_set<Object*> OwnedComponents;
};

template <typename T>
T* Object::FindComponent(const std::string& ComponentName) const
{
	for (Object* Compoent : OwnedComponents)
	{
		if (Compoent && Compoent->GetName() == ComponentName)
		{
			T* CastCompoent = dynamic_cast<T*>(Compoent);
			return CastCompoent;
		}
	}
	return nullptr;
}

template <typename T, typename... Arguments>
T* Object::AddComponent(Arguments&&... Args)
{
	static_assert(std::is_base_of_v<class Component, T>, "T 는 Component 또는 그 파생만 허용합니다.");
	
	T* NewComponent = new T(std::forward<Arguments>(Args)...);
	OwnedComponents.emplace(NewComponent);
	return NewComponent;
}