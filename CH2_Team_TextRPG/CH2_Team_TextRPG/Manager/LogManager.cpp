#include "pch.h"
#include "LogManager.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

void LogManager::AddLog(const std::string& Message)
{
    Logs.push_back(Message);
}

void LogManager::PrintRecentLogs(int Count) const
{
    std::cout << "\n=== 최근 로그 ===\n";

    if (Logs.empty())
    {
        std::cout << "> 로그가 없습니다.\n";
        return;
    }

    int StartIndex = std::max(0, static_cast<int>(Logs.size()) - Count);

    for (int i = StartIndex; i < static_cast<int>(Logs.size()); i++)
    {
        std::cout << "> " << Logs[i] << '\n';
    }
}

void LogManager::PrintAllLogs() const
{
    std::cout << "\n=== 전체 로그 ===\n";

    if (Logs.empty())
    {
        std::cout << "> 로그가 없습니다.\n";
        return;
    }

    for (const std::string& Log : Logs)
    {
        std::cout << "> " << Log << '\n';
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