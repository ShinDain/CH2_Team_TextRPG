#pragma once

class IDamageable
{
public:
	virtual void TakeDamage(int Damage) = 0;
	virtual bool IsDead() const = 0;
};
