#include "pch.h"
#include "UI/JobSelectUIFlow.h"
#include "Core/GameInstance.h"
#include "Manager/InputManager.h"
#include "Manager/LogManager.h"
#include "UI/JobSelectUIScreen.h"

EJobSelectUIResult JobSelectUIFlow::Process()
{
	JobSelectUIScreen::Draw();

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult)
	{
		GameInstance::GetInstance().GetLogManager().AddLog("잘못된 입력입니다.");
		return EJobSelectUIResult::None;
	}

	if (Input == 0)
	{
		return EJobSelectUIResult::BackToStart;
	}

	if (Input >= 1 && Input <= 3)
	{
		// TODO: 직업 번호를 기준으로 실제 캐릭터 생성 로직 연결.
		GameInstance::GetInstance().GetLogManager().AddLog("직업 선택 데이터 연결 대기 중입니다.");
		return EJobSelectUIResult::WaitingForCharacterConnection;
	}

	GameInstance::GetInstance().GetLogManager().AddLog("직업 번호를 다시 선택해주세요.");
	return EJobSelectUIResult::None;
}
