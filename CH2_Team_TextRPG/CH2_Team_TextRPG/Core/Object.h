#pragma once

class Object
{
public:
	Object();
	Object(const std::string& InName);

	bool Initialize();

	const std::string& GetName() { return Name; }
protected:
	std::string Name;
};

