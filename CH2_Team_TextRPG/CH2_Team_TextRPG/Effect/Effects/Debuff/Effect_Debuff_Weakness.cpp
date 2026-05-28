#include "pch.h"
#include "Effect_Debuff_Weakness.h"
#include "Effect/EffectTag.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"

Effect_Debuff_Weakness::Effect_Debuff_Weakness(int InValue)
	: Effect(Game::EffectTag::Debuff::Weakness, InValue)
{
}

void Effect_Debuff_Weakness::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		if (auto TargetStat = dynamic_cast<IUnitStat*>(Target))
		{
			int CurrentStat = TargetStat->GetStat(EStatType::Attack);
			int Decrease = std::min(CurrentStat, Value);
			if (Decrease < 0) Decrease = 0;

			AppliedValues[Target] += Decrease;
			TargetStat->ApplyStat(EStatType::Attack, -Decrease);
			GLog.AddLog("[약화] " + Target->GetName() + "의 공격력이 " + std::to_string(Decrease) + " 감소했습니다.");
		}
	}
}

void Effect_Debuff_Weakness::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		if (auto TargetStat = dynamic_cast<IUnitStat*>(Target))
		{
			int RecoverValue = AppliedValues[Target];
			TargetStat->ApplyStat(EStatType::Attack, RecoverValue);
			GLog.AddLog("[디버프 해제] " + Target->GetName() + "의 약화 상태가 해제되었습니다.");
			AppliedValues.erase(Target);
		}
	}
}