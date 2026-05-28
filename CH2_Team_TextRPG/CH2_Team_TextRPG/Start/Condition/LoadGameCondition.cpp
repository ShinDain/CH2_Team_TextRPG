#include "pch.h"
#include "LoadGameCondition.h"

LoadGameCondition::LoadGameCondition()
{
}

LoadGameCondition::~LoadGameCondition()
{
}

void LoadGameCondition::Init()
{
	GLog.PrintLogOnce("LoadGameCondition Init!");
}

void LoadGameCondition::OnNotify()
{
	GLog.PrintLogOnce("LoadGameCondition Notified!");
}

bool LoadGameCondition::Check()
{
	GLog.PrintLogOnce("LoadGameCondition Checked!");
	return false;
}
