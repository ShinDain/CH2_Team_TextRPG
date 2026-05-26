#include "pch.h"
#include "LogManager.h"
#include "Manager/InputManager.h"

#include <algorithm>

void LogManager::AddLog(const std::string& Message)
{
    Logs.push_back(Message);
}

void LogManager::PrintRecentLogs(int Count) const
{
    GInput << "\n=== 최근 로그 ===\n";

    if (Logs.empty())
    {
        GInput << "> 로그가 없습니다.\n";
        return;
    }

    int StartIndex = std::max(0, static_cast<int>(Logs.size()) - Count);

    for (int i = StartIndex; i < static_cast<int>(Logs.size()); i++)
    {
        GInput << "> " << Logs[i] << '\n';
    }
}

void LogManager::PrintAllLogs() const
{
    GInput << "\n=== 전체 로그 ===\n";

    if (Logs.empty())
    {
        GInput << "> 로그가 없습니다.\n";
        return;
    }

    for (const std::string& Log : Logs)
    {
        GInput << "> " << Log << '\n';
    }
}

std::vector<std::string> LogManager::GetRecentLogs(int Count) const
{
    std::vector<std::string> RecentLogs;

    if (Logs.empty())
    {
        return RecentLogs;
    }

    int StartIndex = std::max(0, static_cast<int>(Logs.size()) - Count);

    for (int i = StartIndex; i < static_cast<int>(Logs.size()); i++)
    {
        RecentLogs.push_back(Logs[i]);
    }

    return RecentLogs;
}
