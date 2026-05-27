#pragma once

class Component;

class Object
{
public:
	Object();
	Object(const std::string& InName);
	virtual ~Object() = default;

	const std::string& GetName() const { return Name; }

	virtual bool Initialize() = 0;

	void AddComponent(const std::shared_ptr<Component>& InComp);
	void RemoveComponent(const std::shared_ptr<Component>& InComp);

	template <typename T>
	std::shared_ptr<T> FindComponent(const std::string& ComponentName) const;

	template <typename T, typename... Arguments>
	std::shared_ptr<T> AddComponent(Arguments&&... Args);

protected:
	std::string Name;

private:
	std::vector<std::shared_ptr<Object>> OwnedComponents;
};

template <typename T>
std::shared_ptr<T> Object::FindComponent(const std::string& ComponentName) const
{
	for (const auto& Comp : OwnedComponents)
	{
		if (Comp && Comp->GetName() == ComponentName)
		{
			if (auto Casted = std::dynamic_pointer_cast<T>(Comp))
				return Casted;
		}
	}
	return nullptr;
}

template <typename T, typename... Arguments>
std::shared_ptr<T> Object::AddComponent(Arguments&&... Args)
{
	static_assert(std::is_base_of_v<class Component, T>, "T 는 Component 또는 그 파생만 허용합니다.");

	auto NewComponent = std::make_shared<T>(std::forward<Arguments>(Args)...);
	OwnedComponents.push_back(NewComponent);
	return NewComponent;
}
