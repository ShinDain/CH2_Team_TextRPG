#pragma once

#include <memory>
#include <string>

struct UserData;

class UserSaveManager
{
public:
	UserSaveManager();
	virtual ~UserSaveManager() = default;

	bool Save() const;
	bool Save(const UserData& InData);
	bool SaveSnapShot();

	bool Load();

	UserData GetUserData() const;

	bool HasLoadedData() const;

private:
	void UpdateUserData();
	std::string GetSavePath() const;

private:
	std::unique_ptr<UserData> CachedUserData;
	bool bHasLoadedData = false;
};
