#pragma once
#include "Core/Condition.h"
#include "Manager/ObjectManager.h"
#include "Manager/CombatManager.h"
#include "Character/Player/Player.h"

class CombatVictoryCondition : public ICondition {
public:
    virtual void Init() override {
		// TODO : 몬스터 사망 시 알림 등록 로직
    }
    virtual void OnNotify() override {
        // TODO : 몬스터 사망 시 알림 처리 로직
	}
    virtual bool Check() override {
        Player* player = ObjectManager::GetInstance().FindObject<Player>("Player");
        return CombatManager::GetInstance().GetAliveMonsters().empty() && player && !player->IsDead();
    }
};


class CombatDefeatCondition : public ICondition {
public:
    virtual void Init() override {
		// TODO : 플레이어 사망 시 알림 등록 로직
    }
    virtual void OnNotify() override {
        // TODO : 플레이어 사망 시 알림 처리 로직
    }
    virtual bool Check() override {
        Player* player = ObjectManager::GetInstance().FindObject<Player>("Player");
        if (player)
        {
            return player->IsDead();
        }
        return false;
    }
};
