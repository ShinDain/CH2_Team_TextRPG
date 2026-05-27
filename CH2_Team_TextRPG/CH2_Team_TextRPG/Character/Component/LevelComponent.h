#pragma once
#include "Core/Component.h"

class LevelComponent : public Component
{
public:
	LevelComponent(Object* InOwner);
	~LevelComponent() override = default;

	bool Initialize() override;

	bool IsMaxLevel() const;
	void AddExp(int Amount);

	int GetLevel() const { return CurrentLevel; }
	int GetExp() const { return CurrentExp; }
	int GetExpToNextLevel() const;

private:
	void CheckLevelUp();
	void LevelUp();
	void ApplyLevelupEvent(int Level);

private:
	std::function<void(int)> OnLevelUp;
	int CurrentLevel;
	int MaxLevel;
	int CurrentExp;
};
