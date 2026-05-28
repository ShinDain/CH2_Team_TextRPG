#pragma once

enum class EResourceType;

class IResource
{
public:
	virtual ~IResource() = default;
	virtual int GetCurrentResource(EResourceType Type) const = 0;
	virtual int GetMaxResource(EResourceType Type) const = 0;
	virtual void Decrease(EResourceType Type, int Amount) = 0;
	virtual void Recovery(EResourceType Type, int Amount) = 0;
	virtual void Restore(EResourceType Type) = 0;
	virtual void RestoreAll() = 0;
};
