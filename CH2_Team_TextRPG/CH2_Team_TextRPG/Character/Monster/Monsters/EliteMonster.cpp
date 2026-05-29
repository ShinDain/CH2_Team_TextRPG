#include "pch.h"
#include "EliteMonster.h"
#include "Character/Component/ResourceComponent.h"
#include "Character/Player/Player.h"
#include "Data/Character/Damage.h"
#include "Data/Character/Stat.h"
#include <Manager/RecordManager.h>

#define COMPONENT_CHECK(x) assert((x) && #x "Component 생성되지 않음")

EliteMonster::EliteMonster(MonsterSetData&& Desc)
    : Monster(std::move(Desc))
{
        AttackCount = 0;
}

void EliteMonster::Decrease(EResourceType Type, int Amount)
{
	COMPONENT_CHECK(Resource);
	Resource->Decrease(Type, Amount);
	if (Resource->GetCurrent(EResourceType::Health) <= 0)
	{
		RecordManager::GetInstance().IncrementEliteKills();
	}
}