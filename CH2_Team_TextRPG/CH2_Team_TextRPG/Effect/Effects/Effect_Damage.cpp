#include "pch.h"
#include "Effect_Damage.h"
#include "Character/Component/ResourceComponent.h"
#include "Character/Interface/UnitStat.h"
#include "Character/Interface/Resource.h"
#include "Data/Character/Stat.h"
#include "Manager/InputManager.h"

Effect_Damage::Effect_Damage(int InValue) : Effect(Game::EffectTag::Damage::Damage, InValue)
{
}

void Effect_Damage::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	IUnitStat* InstigatorStat = dynamic_cast<IUnitStat*>(Instigator);
	if (!InstigatorStat) return;
	int attackerAtk = InstigatorStat->GetStat(EStatType::Attack);

	for (Object* Target : Targets)
	{
		IUnitStat* TargetStat = dynamic_cast<IUnitStat*>(Target);
		auto* TargetHP = dynamic_cast<IResource*>(Target);
		if (!TargetStat || !TargetHP) continue;
		int targetDef = std::max(1, TargetStat->GetStat(EStatType::Defense));

		// 기획서 대미지 계산식: (공격력 * 스킬 배율(Value)) / 방어력
        long long scaledDamage = static_cast<long long>(attackerAtk) * Value;
        long long scaledDef = static_cast<long long>(targetDef) * 10000;
		int actualDamage = static_cast<int>(scaledDamage / scaledDef);
		actualDamage = std::max(0, actualDamage);

		TargetHP->Decrease(EResourceType::Health , actualDamage);
		GLog.AddLog("[" + Instigator->GetName() + "]의 타격! [" + Target->GetName() + "]에게 " + std::to_string(actualDamage) + "의 대미지!");
	}
}

void Effect_Damage::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
}


Effect_Fixed_Damage::Effect_Fixed_Damage(int InValue) : Effect(Game::EffectTag::Damage::FixedDamage, InValue)
{
}

void Effect_Fixed_Damage::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		auto* TargetHP = dynamic_cast<IResource*>(Target);
		if (!TargetHP) continue;
		int actualDamage = std::max(0, Value);
		TargetHP->Decrease(EResourceType::Health , actualDamage);
		GLog.AddLog("[" + Instigator->GetName() + "]의 타격! [" + Target->GetName() + "]에게 " + std::to_string(actualDamage) + "의 고정 대미지!");
	}
}

void Effect_Fixed_Damage::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
}