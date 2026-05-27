#pragma once

enum class EResourceType;

class IResource
{
public:
	virtual ~IResource() = default;
	virtual void Recovery(EResourceType Type, int Amount) = 0;
	virtual void Restore(EResourceType Type) = 0;
	virtual void RestoreAll() = 0;
};
