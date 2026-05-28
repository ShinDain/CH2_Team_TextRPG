#pragma once
#include "pch.h"
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"

struct DamageContext;
class Player;
struct MonsterSetData
{
    std::string Name;
	int DropItemId;
    int HP;
    int Attack;
    int Defence;
	int DropGold;
    int Exp;

    MonsterSetData() :
        HP(0),
        Attack(0),
        Defence(0),
		DropItemId(0),
        Exp(0),
		DropGold(0)
    {
    }

    MonsterSetData(const std::string& Name, int DropItemId,
        int HP, int Attack, int Defence,
        int DropGold, int Exp) :
        Name(Name),
		DropItemId(DropItemId),
        HP(HP),
        Attack(Attack),
        Defence(Defence),
		DropGold(DropGold),
        Exp(Exp)
    {
    }

    MonsterSetData(const MonsterSetData& Other) :
        Name(Other.Name),
		DropItemId(Other.DropItemId),
        HP(Other.HP),
        Attack(Other.Attack),
        Defence(Other.Defence),
		DropGold(Other.DropGold),
        Exp(Other.Exp)
    {
    }

    MonsterSetData(MonsterSetData&& Other) noexcept :
        Name(std::move(Other.Name)),
		DropItemId(std::move(Other.DropItemId)),
        HP(Other.HP),
        Attack(Other.Attack),
        Defence(Other.Defence),
		DropGold(Other.DropGold),
        Exp(Other.Exp)
    {
    }

    MonsterSetData& operator=(const MonsterSetData& Other)
    {
        Name = Other.Name;
		DropItemId = Other.DropItemId;
        HP = Other.HP;
        Attack = Other.Attack;
        Defence = Other.Defence;
		DropGold = Other.DropGold;
        Exp = Other.Exp;
        return *this;
    }
};
class Monster : public Character, public IDamageable
{
public:
    Monster() = delete;
    Monster(MonsterSetData&& Desc);
    virtual ~Monster();

    virtual void Attack(Player* player);
    // IDamageable
    void TakeDamage(int Damage) override;
    bool IsDead() const override;

    void Reset();

    // Stat
    std::string GetName() const;
    int GetHP() const;
    int GetAttack() const;
    int GetDefence() const;
    int GetExp() const;
    int GetDropItemId() const;
    int GetDropGold() const;
    bool Initialize() override;

protected:
    MonsterSetData MonsterData;
    MonsterSetData OriginalData;
};


