#pragma once
#include "pch.h"
#include "Character/Character.h"
#include "Character/Interface/Damageable.h"
#include "Character/Interface/Resource.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Damage.h"

struct DamageContext;
class Player;
struct MonsterSetData
{
    std::string Name;
	int DropItemId;
    int HP;
    int Attack;
    int Defense;
    int ActionSpeed;
	int DropGold;
    int Exp;
    std::vector<int> Skills;

    MonsterSetData() : 
        Name(""),
        DropItemId(0), 
        HP(0), 
        Attack(0), 
        Defense(0), 
        ActionSpeed(0), 
        DropGold(0), 
        Exp(0),
        Skills()
    {
    }

    MonsterSetData(const std::string& Name, int DropItemId, 
        int HP, int Attack, int Defense, 
        int ActionSpeed, int DropGold, int Exp, const std::vector<int>& Skills) :
        Name(Name), 
        DropItemId(DropItemId), 
        HP(HP), 
        Attack(Attack), 
        Defense(Defense), 
        ActionSpeed(ActionSpeed), 
        DropGold(DropGold), 
        Exp(Exp),
        Skills(Skills)
    {
    }

    MonsterSetData(const MonsterSetData& Other) :
        Name(Other.Name),
        DropItemId(Other.DropItemId),
        HP(Other.HP),
        Attack(Other.Attack),
        Defense(Other.Defense),
        ActionSpeed(Other.ActionSpeed),
        DropGold(Other.DropGold),
        Exp(Other.Exp),
		Skills(Other.Skills)
    {
    }

    MonsterSetData(MonsterSetData&& Other) noexcept :
        Name(std::move(Other.Name)),
        DropItemId(std::move(Other.DropItemId)),
        HP(Other.HP),
        Attack(Other.Attack),
        Defense(Other.Defense),
        ActionSpeed(Other.ActionSpeed),
        DropGold(Other.DropGold),
        Exp(Other.Exp),
		Skills(std::move(Other.Skills))
    {
    }

    MonsterSetData& operator=(const MonsterSetData& Other)
    {
        Name = Other.Name;
        DropItemId = Other.DropItemId;
        HP = Other.HP;
        Attack = Other.Attack;
        Defense = Other.Defense;
		ActionSpeed = Other.ActionSpeed;
        DropGold = Other.DropGold;
        Exp = Other.Exp;
		Skills = Other.Skills;
        return *this;
    }
};
class Monster : public Character, public IDamageable, public IUnitStat, public IResource
{
public:
    Monster() = delete;
    Monster(MonsterSetData&& Desc);
    virtual ~Monster();

    bool Initialize() override;

    void TakeDamage(int Damage) override;      
    bool IsDead() const override;

    void Decrease(EResourceType Type, int Amount) override;
    void Recovery(EResourceType Type, int Amount) override;
    void Restore(EResourceType Type) override;
    void RestoreAll() override;

    void ApplyStat(EStatType Type, int Delta) override;
    void SetBaseStat(EStatType Type, int Value);
    
    // getters
    int GetStat(EStatType Type) const override;
    int GetCurrentResource(EResourceType Type) const override;
    int GetMaxResource(EResourceType Type) const override;
    std::string GetName() const;
    int GetActionSpeed() const;
    int GetExp() const;
    int GetDropItemId() const;
    int GetDropGold() const;
    
protected:
    MonsterSetData MonsterData;
    MonsterSetData OriginalData;
    std::shared_ptr<class StatComponent> Stat;
    std::shared_ptr<class ResourceComponent> Resource;
    std::shared_ptr<class EffectComponent> Effect;
    std::shared_ptr<class SkillComponent> Skill;
};


