#include "pch.h"
#include "LogManager.h"

#include <iostream>
#include <algorithm>

void LogManager::AddLog(const std::string& Message)
{
    Logs.push_back(Message);
}

void LogManager::PrintRecentLogs(int Count) const
{
    std::cout << "\n=== Recent Logs ===\n";

    if (Logs.empty())
    {
        std::cout << "> No logs yet.\n";
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
    std::cout << "\n=== All Logs ===\n";

    if (Logs.empty())
    {
        std::cout << "> No logs yet.\n";
        return;
    }

    for (const std::string& Log : Logs)
    {
        std::cout << "> " << Log << '\n';
    }
}