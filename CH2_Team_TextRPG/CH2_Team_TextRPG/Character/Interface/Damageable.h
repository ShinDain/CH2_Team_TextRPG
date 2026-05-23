#pragma once

class IDamageable
{
public:
	virtual void TakeDamage(const struct DamageContext& Context) = 0;
	virtual bool IsDead() const = 0;
};
