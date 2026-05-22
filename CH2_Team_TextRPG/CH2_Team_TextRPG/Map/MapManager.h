#pragma once

#include <vector>
#include <string>

enum class ENodeType
{
    Start,
    Monster,
    Elite,
    Event,
    Shop,
    Treasure,
    Rest,
    Boss
};

struct MapNode
{
    int Id = -1;
    ENodeType Type = ENodeType::Start;
    int Floor = 0;
    bool bIsVisited = false;
    std::vector<int> ConnectedNodeIds;
};

class MapManager
{
private:
    std::vector<MapNode> Nodes;
    int CurrentNodeId = 0;

public:
    void GenerateFixedMap();

    const MapNode* GetCurrentNode() const;
    const MapNode* GetNodeById(int NodeId) const;

    std::vector<int> GetMovableNodeIds() const;

    bool MoveToNode(int NodeId);

    void PrintCurrentNode() const;
    void PrintMovableNodes() const;
    void PrintSimpleMap() const;

    bool IsBossNode() const;

    static std::string NodeTypeToString(ENodeType Type);
};