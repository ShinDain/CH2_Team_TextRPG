#pragma once
#include "Character/Character.h"
#include "Core/Object.h"


/** 타임라인 계산 전용 경량 구조체 */
struct FTimelineNode
{
	Object* unit;
	float ActionValue;	// 현재 행동 수치 ( 0에 도달하면 행동 가능 )

    bool operator<(const FTimelineNode& Other) const
    {
        return ActionValue < Other.ActionValue;
    }
};


class TurnManager
{
public:
	TurnManager() = default;
	~TurnManager();

	/**
	 * @brief 캐릭터를 타임라인에 추가
	 * @param character 타임라인에 추가할 캐릭터에 대한 포인터.
	 */
	void AddCharacterToTimeline(Object* character);

	/**
	 * @brief 대기열 정렬 후 다음 턴 캐릭터 반환
	 * @return 다음 턴 캐릭터에 대한 포인터.
	 */	
	Object* GetNextTurnCharacter();

	/**
	 * @brief 캐릭터의 행동 수치를 초기화
	 * @param character 행동 수치를 초기화할 캐릭터에 대한 포인터.
	 */
	void ResetCharacterTurn(Object* character);

	/**
	 * @brief 캐릭터의 행동 수치 증가
	 * @param character 행동 수치를 증가시킬 캐릭터에 대한 포인터.
	 * @param value 행동 수치에 추가할 값.
	 */
	void AddActionValue(Object* character, float value);
private:

	/**
	 * @brief 캐릭터의 행동 속도 계산
	 * @param character 행동 속도를 계산할 캐릭터에 대한 포인터.
	 * @return 캐릭터의 행동 속도에 따른 수치.
	 */
	float GetCharacterSpeed(Object* character) const;


private:
	const float TurnThreshold = 1000.0f;	// 행동 수치가 이 값에 도달하면 행동 가능
	std::vector<FTimelineNode> turnQueue;
};