#pragma once

#include <string>
#include <vector>

class LogManager
{
private:
    std::vector<std::string> Logs;

public:
    void AddLog(const std::string& Message);
    void PrintLogOnce(const std::string& Message);

    void PrintRecentLogs(int Count) const;
    void PrintAllLogs() const;

    std::vector<std::string> GetRecentLogs(int Count) const;
};