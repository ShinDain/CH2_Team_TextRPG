#pragma once

class InputManager;
class InputSession
{
public:
	InputSession(InputManager* InSystem);
	InputSession(InputSession&& Other) noexcept;
	~InputSession();

	template <typename Ty>
	InputSession& operator>>(Ty& RHS);
	explicit operator bool() const;

private:
	InputManager* InputSystem;
};

class InputManager
{
	friend InputSession;
	
public:
	InputManager();
	~InputManager() = default;
	bool IsFailed() const;
	void SetInputLocked(bool bLocked);
	bool IsInputLocked() const;
	void ClearInputBuffer();

	template <typename Ty>
	InputSession operator>>(Ty& RHS)
	{
		InputSession Session(this);
		Session >> RHS;
		return Session;
	}

	template <typename Ty>
	InputManager& operator<<(const Ty& RHS)
	{
		std::cout << RHS;
		return *this;
	}
	
private:
	void ApplyFail();
	void ClearBuffer();
	void Reset();

private:
	bool bFailed;
	bool bInputLocked;
};

class InputLockGuard
{
public:
	explicit InputLockGuard(InputManager& InInputManager);
	~InputLockGuard();

	InputLockGuard(const InputLockGuard&) = delete;
	InputLockGuard& operator=(const InputLockGuard&) = delete;

private:
	InputManager& InputSystem;
	bool bPreviousLockState;
};

template <typename Ty>
InputSession& InputSession::operator>>(Ty& RHS)
{
	if (InputSystem->IsInputLocked())
	{
		InputSystem->ApplyFail();
		InputSystem->ClearInputBuffer();
		return *this;
	}

	if (InputSystem->IsFailed())
	{
		return *this;
	}

	std::cin >> RHS;
	if (std::cin.fail())
	{
		InputSystem->ApplyFail();
	}
	return *this;
}
