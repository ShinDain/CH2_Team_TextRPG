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
	void WaitForKey();

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
		std::cout << "잘못된 입력" << "\n"; // 현재 잘못된 입력처리에 대한 텍스트 내용이 없어 임시 텍스트 출력
		InputSystem->ApplyFail();
	}
	return *this;
}
