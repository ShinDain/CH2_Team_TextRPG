#pragma once
#include "Monster.h"

class Player;

class Slime : public Monster
{
public:
	Slime();
	Slime(MonsterSetData&& Desc);
	virtual ~Slime();
	
	void Attack(Player* Target) override;
	bool Initialize() override;
private:
	static MonsterSetData GenerateStat(Player* player);  // 랜덤 스탯 생성
};
