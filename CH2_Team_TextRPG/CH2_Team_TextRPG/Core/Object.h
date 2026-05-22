#pragma once

class Object
{
public:
	Object();
	Object(const std::string& InName);

	const std::string& GetName() { return Name; }
protected:
	std::string Name;
};

