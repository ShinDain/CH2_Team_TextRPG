#pragma once
#include "pch.h"
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"
#include "Character/Interface/UnitStat.h"

class Player;
struct DamageContext;
struct MonsterSetData
{
    std::string Name;
    std::string DropItemName;
    int HP;
    int Attack;
    int Defence;
    int DropItemPrice;
    int Exp;

    MonsterSetData() :
        HP(0),
        Attack(0),
        Defence(0),
        DropItemPrice(0),
        Exp(0)
    {
    }

    MonsterSetData(const std::string& Name, const std::string& DropItemName,
        int HP, int Attack, int Defence,
        int DropItemPrice, int Exp) :
        Name(Name),
        DropItemName(DropItemName),
        HP(HP),
        Attack(Attack),
        Defence(Defence),
        DropItemPrice(DropItemPrice),
        Exp(Exp)
    {
    }

    MonsterSetData(const MonsterSetData& Other) :
        Name(Other.Name),
        DropItemName(Other.DropItemName),
        HP(Other.HP),
        Attack(Other.Attack),
        Defence(Other.Defence),
        DropItemPrice(Other.DropItemPrice),
        Exp(Other.Exp)
    {
    }

    MonsterSetData(MonsterSetData&& Other) noexcept :
        Name(std::move(Other.Name)),
        DropItemName(std::move(Other.DropItemName)),
        HP(Other.HP),
        Attack(Other.Attack),
        Defence(Other.Defence),
        DropItemPrice(Other.DropItemPrice),
        Exp(Other.Exp)
    {
    }

    MonsterSetData& operator=(const MonsterSetData& Other)
    {
        Name = Other.Name;
        DropItemName = Other.DropItemName;
        HP = Other.HP;
        Attack = Other.Attack;
        Defence = Other.Defence;
        DropItemPrice = Other.DropItemPrice;
        Exp = Other.Exp;
        return *this;
    }
};
class Monster : public Character, public IUnitStat, public IDamageable
{
public:
    Monster() = delete;
    Monster(MonsterSetData&& Desc);
    virtual ~Monster();

    virtual void Attack(Player* player);
    // IDamageable
    void TakeDamage(const struct DamageContext& Context) override;
    bool IsDead() const override;

    void Reset();

    // IUnitStat
    int GetStat(EStatType Type) const override;
    std::string GetName() const;
    int GetHP() const;
    int GetMP() const;
    int GetAttack() const;
    int GetDefence() const;
    int GetExp() const;

    std::string GetDropItemName() const;
    int GetDropItemPrice() const;

    bool Initialize() override;

protected:
        MonsterSetData MonsterData;
        MonsterSetData OriginalData;
    };


