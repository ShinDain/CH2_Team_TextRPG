#include "pch.h"
#include "Effect_Debuff_Slow.h"
#include "Effect/EffectTag.h"
#include "Character/Interface/UnitStat.h"
#include "Data/Character/Stat.h"
#include <algorithm>

Effect_Debuff_Slow::Effect_Debuff_Slow(int InValue)
	: Effect(Game::EffectTag::Debuff::Slow, InValue)
{
}

void Effect_Debuff_Slow::Apply(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		if (auto TargetStat = dynamic_cast<IUnitStat*>(Target))
		{
			TargetStat->ApplyStat(EStatType::ActionSpeed, -Value);
			GLog.AddLog("[둔화] " + Target->GetName() + "의 행동 속도가 " + std::to_string(Value) + " 감소했습니다.");
			int CurrentStat = TargetStat->GetStat(EStatType::ActionSpeed);
			int Decrease = std::min(CurrentStat, Value);
			if (Decrease < 0) Decrease = 0;

			AppliedValues[Target] += Decrease;
			TargetStat->ApplyStat(EStatType::ActionSpeed, -Decrease);
			GLog.AddLog("[둔화] " + Target->GetName() + "의 행동 속도가 " + std::to_string(Decrease) + " 감소했습니다.");
		}
	}
}

void Effect_Debuff_Slow::Remove(Object* Instigator, std::vector<class Object*> Targets)
{
	for (Object* Target : Targets)
	{
		if (auto TargetStat = dynamic_cast<IUnitStat*>(Target))
		{
			TargetStat->ApplyStat(EStatType::ActionSpeed, Value);
			int RecoverValue = AppliedValues[Target];
			TargetStat->ApplyStat(EStatType::ActionSpeed, RecoverValue);
			GLog.AddLog("[디버프 해제] " + Target->GetName() + "의 둔화 상태가 해제되었습니다.");
			AppliedValues.erase(Target);
		}
	}
}