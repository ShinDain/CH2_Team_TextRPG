#pragma once
#include "Character/Interface/UnitStat.h"
#include "Core/Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent(Object* InOwner);
	~HealthComponent() override;
	
	bool Initialize() override;
	
	bool IsDead() const { return CurrentHP <= 0; }
	int GetCurrent() const { return CurrentHP; }
	int GetMax() const;

	void Increase(int Amount);
	void Decrease(int Amount);
	void Restore();
	
private:
	const class IUnitStat* UnitStat;
	int CurrentHP;
};
