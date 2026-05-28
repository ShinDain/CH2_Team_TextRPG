#pragma once

enum class EJobSelectUIResult
{
	None,
	BackToStart,
	WaitingForCharacterConnection
};

class JobSelectUIFlow
{
public:
	static EJobSelectUIResult Process();
};
