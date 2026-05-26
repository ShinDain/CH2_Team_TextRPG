#pragma once
#include "pch.h"
#include "Core/Object.h"

enum class ECharacterType
{
	Player,
	Monster
};

class Character : public Object
{
public:
	Character();
	virtual ~Character();
	bool Initialize() override;
	
	ECharacterType GetCharacterType() const { return CharacterType; }
	
protected:
	ECharacterType CharacterType;
};
