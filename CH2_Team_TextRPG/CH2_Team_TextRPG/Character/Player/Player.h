#pragma once
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"
#include "Character/Interface/UnitStat.h"

class Player : public Character, public IDamageable, public IUnitStat
{
public:
	Player();
	~Player() override;
	
	bool Initialize() override;
	void TakeDamage(const DamageContext& Context) override;
	bool IsDead() const override;
	int GetStat(EStatType Type) const override;
};
