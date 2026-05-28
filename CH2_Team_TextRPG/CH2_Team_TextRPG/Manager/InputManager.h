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
};

template <typename Ty>
InputSession& InputSession::operator>>(Ty& RHS)
{
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
