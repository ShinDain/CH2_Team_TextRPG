#include "pch.h"
#include "StartNextCondition.h"

#include "Character/Player/Player.h"
#include "Manager/ObjectManager.h"

StartNextCondition::~StartNextCondition()
{
}

void StartNextCondition::Init()
{
	Player* LoadPlayer = ObjectManager::GetInstance().FindObject<Player>("Player");
	LoadPlayer->RestoreAll();
}

void StartNextCondition::OnNotify()
{
	
}

bool StartNextCondition::Check()
{
	return AlwaysTrueCondition::Check();
}
