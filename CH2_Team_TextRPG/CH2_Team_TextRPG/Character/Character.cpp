#include "pch.h"
#include "Character.h"

Character::Character()
	:Object(), CharacterType(ECharacterType::End)
{
}

Character::~Character()
{
}

bool Character::Initialize()
{
	return false;
}