#pragma once
#include <map>
#include "Map/MapManager.h"

enum class ENodeType;

class RecordManager
{
private:
    RecordManager();
    RecordManager(const RecordManager& rhs) = delete;
    RecordManager& operator=(const RecordManager& rhs) = delete;

public:
    ~RecordManager() = default;
    static RecordManager& GetInstance();

	void Initialize();

    void IncrementMonsterKills();
    void IncrementEliteKills();
    void AddNodeVisitCount(ENodeType Type);

    int GetMonsterKills() const { return MonsterKills; }
    int GetEliteKills() const { return EliteKills; }
    int GetNodeVisitCount(ENodeType Type) const;
    int GetTotalNodeVisits() const;

private:
    int MonsterKills;
    int EliteKills;

    std::map<ENodeType, int> NodeVisitCounts;
};