#pragma once
#include "Core/Component.h"

class LevelComponent : public Component
{
public:
	using OnLevelUpCallback = std::function<void(int NewLevel)>;
	
public:
	LevelComponent(Object* InOwner);
	~LevelComponent() override;

	bool Initialize() override;

	bool IsMaxLevel() const;
	
	void SetExp(int NewExp);
	void AddExp(int Amount);
	void ReviveLevel(int TargetLevel);

	int GetLevel() const { return CurrentLevel; }
	int GetExp() const { return CurrentExp; }
	int GetExpToNextLevel() const;
	
	void BindOnLevelUp(const OnLevelUpCallback& Subscriber);
	void UnbindOnLevelup();

private:
	void CheckLevelUp();
	void LevelUp();
	void ApplyLevelupEvent(int Level);

private:
	OnLevelUpCallback OnLevelUp;
	int CurrentLevel;
	int MaxLevel;
	int CurrentExp;
	
};
