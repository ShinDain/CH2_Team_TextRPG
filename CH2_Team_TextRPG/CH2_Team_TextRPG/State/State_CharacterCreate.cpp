#include "pch.h"
#include "State_CharacterCreate.h"
#include "Character/Player/CharacterCreator.h"
#include "Core/GameInstance.h"
#include "Data/Character/CharacterJobRepository.h"
#include "Manager/InputManager.h"
#include "Manager/LogManager.h"
#include "Manager/StateManager.h"
#include "UI/CharacterCreateScreen.h"

State_CharacterCreate::State_CharacterCreate()
{
	Name = "CharacterCreate";
}

void State_CharacterCreate::Enter()
{
	Jobs.clear();

	LogManager& Log = GameInstance::GetInstance().GetLogManager();
	if (!CharacterJobRepository::LoadCharacterJobs(Jobs, Log))
	{
		StateManager::GetInstance().ChangeState(EState::Start);
	}
}

void State_CharacterCreate::Process()
{
	if (Jobs.empty())
	{
		StateManager::GetInstance().ChangeState(EState::Start);
		return;
	}

	CharacterCreateScreen::DrawJobSelectionScreen(Jobs);

	int Input = -1;
	InputSession InputResult = GInput >> Input;

	if (!InputResult || Input < 1 || Input > static_cast<int>(Jobs.size()))
	{
		GameInstance::GetInstance().GetLogManager().AddLog("잘못된 직업 번호입니다.");
		return;
	}

	const CharacterJobData& SelectedJob = Jobs[Input - 1];
	if (CharacterCreator::CreatePlayerFromJob(GameInstance::GetInstance(), SelectedJob))
	{
		StateManager::GetInstance().ChangeState(EState::Map);
	}
}

void State_CharacterCreate::Exit()
{
	Jobs.clear();
}
