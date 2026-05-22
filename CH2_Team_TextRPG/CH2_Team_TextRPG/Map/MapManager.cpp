#include "pch.h"
#include "MapManager.h"

#include <iostream>

void MapManager::GenerateFixedMap()
{
    Nodes.clear();

    /*
        Fixed Map Structure

              [Boss: 6]
               /     \
          [Rest:4]  [Elite:5]
             |          |
          [Shop:2]  [Monster:3]
              \      /
             [Event:1]
                |
             [Start:0]
    */

    MapNode Start;
    Start.Id = 0;
    Start.Type = ENodeType::Start;
    Start.Floor = 0;
    Start.bIsVisited = true;
    Start.ConnectedNodeIds = { 1 };

    MapNode Event;
    Event.Id = 1;
    Event.Type = ENodeType::Event;
    Event.Floor = 1;
    Event.ConnectedNodeIds = { 2, 3 };

    MapNode Shop;
    Shop.Id = 2;
    Shop.Type = ENodeType::Shop;
    Shop.Floor = 2;
    Shop.ConnectedNodeIds = { 4 };

    MapNode Monster;
    Monster.Id = 3;
    Monster.Type = ENodeType::Monster;
    Monster.Floor = 2;
    Monster.ConnectedNodeIds = { 5 };

    MapNode Rest;
    Rest.Id = 4;
    Rest.Type = ENodeType::Rest;
    Rest.Floor = 3;
    Rest.ConnectedNodeIds = { 6 };

    MapNode Elite;
    Elite.Id = 5;
    Elite.Type = ENodeType::Elite;
    Elite.Floor = 3;
    Elite.ConnectedNodeIds = { 6 };

    MapNode Boss;
    Boss.Id = 6;
    Boss.Type = ENodeType::Boss;
    Boss.Floor = 4;
    Boss.ConnectedNodeIds = {};

    Nodes.push_back(Start);
    Nodes.push_back(Event);
    Nodes.push_back(Shop);
    Nodes.push_back(Monster);
    Nodes.push_back(Rest);
    Nodes.push_back(Elite);
    Nodes.push_back(Boss);

    CurrentNodeId = 0;
}

const MapNode* MapManager::GetCurrentNode() const
{
    return GetNodeById(CurrentNodeId);
}

const MapNode* MapManager::GetNodeById(int NodeId) const
{
    for (const MapNode& Node : Nodes)
    {
        if (Node.Id == NodeId)
        {
            return &Node;
        }
    }

    return nullptr;
}

std::vector<int> MapManager::GetMovableNodeIds() const
{
    const MapNode* CurrentNode = GetCurrentNode();

    if (CurrentNode == nullptr)
    {
        return {};
    }

    return CurrentNode->ConnectedNodeIds;
}

bool MapManager::MoveToNode(int NodeId)
{
    std::vector<int> MovableNodeIds = GetMovableNodeIds();

    bool bCanMove = false;

    for (int MovableNodeId : MovableNodeIds)
    {
        if (MovableNodeId == NodeId)
        {
            bCanMove = true;
            break;
        }
    }

    if (!bCanMove)
    {
        return false;
    }

    CurrentNodeId = NodeId;

    for (MapNode& Node : Nodes)
    {
        if (Node.Id == CurrentNodeId)
        {
            Node.bIsVisited = true;
            break;
        }
    }

    return true;
}

void MapManager::PrintCurrentNode() const
{
    const MapNode* CurrentNode = GetCurrentNode();

    if (CurrentNode == nullptr)
    {
        std::cout << "Current node not found.\n";
        return;
    }

    std::cout << "\nCurrent Node\n";
    std::cout << "Id    : " << CurrentNode->Id << '\n';
    std::cout << "Type  : " << NodeTypeToString(CurrentNode->Type) << '\n';
    std::cout << "Floor : " << CurrentNode->Floor << '\n';
}

void MapManager::PrintMovableNodes() const
{
    std::vector<int> MovableNodeIds = GetMovableNodeIds();

    std::cout << "\nMovable Nodes\n";

    if (MovableNodeIds.empty())
    {
        std::cout << "No movable nodes.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(MovableNodeIds.size()); i++)
    {
        const MapNode* Node = GetNodeById(MovableNodeIds[i]);

        if (Node == nullptr)
        {
            continue;
        }

        std::cout << i + 1 << ". "
                  << NodeTypeToString(Node->Type)
                  << " [NodeId: " << Node->Id << "]\n";
    }
}

void MapManager::PrintSimpleMap() const
{
    std::cout << "\n=== Dungeon Map ===\n\n";

    std::cout << "              [Boss:6]\n";
    std::cout << "              /      \\\n";
    std::cout << "        [Rest:4]   [Elite:5]\n";
    std::cout << "           |          |\n";
    std::cout << "        [Shop:2]  [Monster:3]\n";
    std::cout << "             \\      /\n";
    std::cout << "            [Event:1]\n";
    std::cout << "                |\n";
    std::cout << "            [Start:0]\n\n";

    std::cout << "Current Position: Node " << CurrentNodeId << "\n";
}

bool MapManager::IsBossNode() const
{
    const MapNode* CurrentNode = GetCurrentNode();

    if (CurrentNode == nullptr)
    {
        return false;
    }

    return CurrentNode->Type == ENodeType::Boss;
}

std::string MapManager::NodeTypeToString(ENodeType Type)
{
    switch (Type)
    {
    case ENodeType::Start:
        return "시작";
    case ENodeType::Monster:
        return "전투";
    case ENodeType::Elite:
        return "엘리트";
    case ENodeType::Event:
        return "이벤트";
    case ENodeType::Shop:
        return "상점";
    case ENodeType::Treasure:
        return "보물";
    case ENodeType::Rest:
        return "휴식";
    case ENodeType::Boss:
        return "보스";
    default:
        return "알 수 없음";
    }
}