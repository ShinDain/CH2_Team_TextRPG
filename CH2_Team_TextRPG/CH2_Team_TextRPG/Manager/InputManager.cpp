#include "pch.h"
#include "InputManager.h"

#include <windows.h>

InputSession::InputSession(InputManager* InSystem) 
	: InputSystem(InSystem)
{
}

InputSession::InputSession(InputSession&& Other) noexcept : InputSystem(Other.InputSystem)
{
	Other.InputSystem = nullptr;
}

InputSession::~InputSession()
{
	if (InputSystem)
	{
		InputSystem->Reset();
		InputSystem->ClearBuffer();
	}
}

InputSession::operator bool() const
{
	return !InputSystem->IsFailed();
}

InputManager::InputManager() 
	: bFailed(false),
	bInputLocked(false)
{
	
}

bool InputManager::IsFailed() const
{
	return bFailed;
}

void InputManager::SetInputLocked(bool bLocked)
{
	bInputLocked = bLocked;
}

bool InputManager::IsInputLocked() const
{
	return bInputLocked;
}

void InputManager::ClearInputBuffer()
{
	ClearBuffer();
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void InputManager::ApplyFail()
{
	bFailed = true;
}

void InputManager::Reset()
{
	bFailed = false;
}

void InputManager::ClearBuffer()
{
	std::cin.clear();
	std::cin.sync();
}

InputLockGuard::InputLockGuard(InputManager& InInputManager)
	: InputSystem(InInputManager),
	bPreviousLockState(InInputManager.IsInputLocked())
{
	InputSystem.SetInputLocked(true);
}

InputLockGuard::~InputLockGuard()
{
	InputSystem.ClearInputBuffer();
	InputSystem.SetInputLocked(bPreviousLockState);
}
