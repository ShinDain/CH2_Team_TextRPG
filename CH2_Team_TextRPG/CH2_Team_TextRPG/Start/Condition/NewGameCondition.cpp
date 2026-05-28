#include "pch.h"
#include "NewGameCondition.h"
#include "Character/Player/Player.h"
#include "Manager/ObjectManager.h"

NewGameCondition::NewGameCondition()
{
}

NewGameCondition::~NewGameCondition()
{
}

void NewGameCondition::Init()
{
	Player* NewPlayer = ObjectManager::GetInstance().CreateObject<Player>();
}

void NewGameCondition::OnNotify()
{
}

bool NewGameCondition::Check()
{
	return false;
}
