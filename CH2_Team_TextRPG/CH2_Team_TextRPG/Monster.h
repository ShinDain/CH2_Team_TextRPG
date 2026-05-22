#pragma once
#include "pch.h"
#include "Character.h"
//데미지어블,유닛스텟 인터페이스

class Player;

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
    void TakeDamage(int damage) override;
    void Reset() override;
    void Die() override;
    void RestoreHP(int Amount) override;
    void RestoreMP(int Amount) override;
    void AttackUp(int Amount) override;
    void DefenceUp(int Amount) override;

    // IUnitStat
    std::string GetName() const override;
    int GetHP() const override;
    int GetMP() const override;
    int GetAttack() const override;
    int GetDefence() const override;
    int GetExp() const override;

    std::string GetDropItemName() const;
    int GetDropItemPrice() const;
    EItemAbility GetItemAbility() const;

    bool Initialize() override;

protected:
    MonsterSetData MonsterData;
    MonsterSetData OriginalData;
};