#pragma once
#include "Core/Condition.h"
#include "Manager/ObjectManager.h"
#include "Manager/CombatManager.h"
#include "Character/Player/Player.h"

class CombatVictoryCondition : public ICondition {
public:
    virtual void Init() override {
    }
    virtual void OnNotify() override {
        GLog.AddLog("몬스터가 전멸했습니다.");
	}
    virtual bool Check() override {
        Player* player = ObjectManager::GetInstance().FindObject<Player>("Player");
        return CombatManager::GetInstance().GetAliveMonsters().empty();
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
