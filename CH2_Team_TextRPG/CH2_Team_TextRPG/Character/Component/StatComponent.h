#pragma once
#include "Core/Component.h"

enum class EStatType;
class StatComponent : public Component
{
public:
	StatComponent(Object* InOwner);
	~StatComponent() override;

	int GetStat(EStatType InType);
	void SetStat(EStatType InType, int Value);
	void AddStat(EStatType InType, int Delta);
	
	bool Initialize() override;
	
private:
	const size_t StatTypeToIndex(EStatType InType);
	
private:
	std::vector<int> Stats;
};