#pragma once
#include "Core/Component.h"

enum class EResourceType;
class IUnitStat;

class ResourceComponent : public Component
{
public:
	ResourceComponent(Object* InOwner);
	~ResourceComponent() override;

	bool Initialize() override;

	int GetCurrent(EResourceType Type) const;
	int GetMax(EResourceType Type) const;

	void Increase(EResourceType Type, int Amount);
	void Decrease(EResourceType Type, int Amount);

	void Restore(EResourceType Type);
	void Restore();

private:
	const IUnitStat* UnitStat;
	std::vector<int> Currents;
};
