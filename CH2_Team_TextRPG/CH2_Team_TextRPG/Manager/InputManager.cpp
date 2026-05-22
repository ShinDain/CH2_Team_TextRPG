#include "pch.h"
#include "InputManager.h"

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
	: bFailed(false)
{
	
}

bool InputManager::IsFailed() const
{
	return bFailed;
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
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
