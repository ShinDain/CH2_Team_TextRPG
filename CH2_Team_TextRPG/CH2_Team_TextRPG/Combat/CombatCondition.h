#pragma once
#include "Core/Condition.h"


class CombatVictoryCondition : public ICondition {
public:
    virtual void Init() override {
		// TODO : 몬스터 사망 시 알림 등록 로직
    }
    virtual void OnNotify() override {
        // TODO : 몬스터 사망 시 알림 처리 로직
	}
    virtual bool Check() override {
		// TODO : 몬스터 객체가 사망했는지 체크
        return false;
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
		// TODO : 플레이어 객체가 사망했는지 체크
        return false;
    }
};
