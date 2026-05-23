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

	template<typename T>
	T* FindComponent(const std::string& ComponentName) const;
	
	template<typename T>
	void AddComponent(const std::string& ComponentName);

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
			assert(CastCompoent && "Cast Failed Please Check");
			return CastCompoent;
		}
	}
	return nullptr;
}

template <typename T>
void Object::AddComponent(const std::string& ComponentName)
{
	T* NewComponent = new T();
	OwnedComponents.emplace(NewComponent);
}
