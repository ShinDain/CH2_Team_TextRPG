#include "pch.h"
#include "MapManager.h"
#include "Manager/RecordManager.h"

void MapManager::GenerateFixedMap()
{
    Nodes.clear();

    auto AddNode = [this](
        int Id,
        ENodeType Type,
        int Floor,
        std::vector<int> ConnectedNodeIds,
        bool bIsVisited = false)
    {
        MapNode Node;
        Node.Id = Id;
        Node.Type = Type;
        Node.Floor = Floor;
        Node.bIsVisited = bIsVisited;
        Node.ConnectedNodeIds = ConnectedNodeIds;
        Nodes.push_back(Node);
    };

    AddNode(0, ENodeType::Start, 0, { 1, 2, 3 }, true);

    AddNode(1, ENodeType::Monster, 1, { 4, 5 });
    AddNode(2, ENodeType::Event, 1, { 4, 5, 6 });
    AddNode(3, ENodeType::Monster, 1, { 5, 6 });

    AddNode(4, ENodeType::Shop, 2, { 7, 8 });
    AddNode(5, ENodeType::Monster, 2, { 7, 8, 9 });
    AddNode(6, ENodeType::Event, 2, { 8, 9 });

    AddNode(7, ENodeType::Monster, 3, { 10, 11 });
    AddNode(8, ENodeType::Event, 3, { 10, 11, 12 });
    AddNode(9, ENodeType::Rest, 3, { 11, 12 });

    AddNode(10, ENodeType::Elite, 4, { 13, 14 });
    AddNode(11, ENodeType::Monster, 4, { 13, 14, 15 });
    AddNode(12, ENodeType::Shop, 4, { 14, 15 });

    AddNode(13, ENodeType::Event, 5, { 16, 17 });
    AddNode(14, ENodeType::Monster, 5, { 16, 17, 18 });
    AddNode(15, ENodeType::Shop, 5, { 17, 18 });

    AddNode(16, ENodeType::Rest, 6, { 19, 20 });
    AddNode(17, ENodeType::Elite, 6, { 19, 20, 21 });
    AddNode(18, ENodeType::Monster, 6, { 20, 21 });

    AddNode(19, ENodeType::Monster, 7, { 22, 23 });
    AddNode(20, ENodeType::Event, 7, { 22, 23, 24 });
    AddNode(21, ENodeType::Shop, 7, { 23, 24 });

    AddNode(22, ENodeType::Elite, 8, { 25, 26 });
    AddNode(23, ENodeType::Monster, 8, { 25, 26, 27 });
    AddNode(24, ENodeType::Rest, 8, { 26, 27 });

    AddNode(25, ENodeType::Event, 9, { 28, 29 });
    AddNode(26, ENodeType::Monster, 9, { 28, 29, 30 });
    AddNode(27, ENodeType::Rest, 9, { 29, 30 });

    AddNode(28, ENodeType::Rest, 10, { 31 });
    AddNode(29, ENodeType::Elite, 10, { 31 });
    AddNode(30, ENodeType::Monster, 10, { 31 });

    AddNode(31, ENodeType::Boss, 11, {});

    MaxNodeId = Nodes[Nodes.size() - 1].Id;
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
            RecordManager::GetInstance().AddNodeVisitCount(Node.Type);
            break;
        }
    }

    return true;
}

void MapManager::SetCurrentNodeId(const int NewId)
{
    CurrentNodeId = std::min(NewId, MaxNodeId);
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

    std::cout << "                              [Boss:31]\n";
    std::cout << "                         /       |       \\\n";
    std::cout << "                  [Rest:28] [Elite:29] [Monster:30]\n";
    std::cout << "                    /       |       \\\n";
    std::cout << "                [Event:25] [Monster:26] [Rest:27]\n";
    std::cout << "                    \\       |       /\n";
    std::cout << "                [Elite:22] [Monster:23] [Rest:24]\n";
    std::cout << "                    /       |       \\\n";
    std::cout << "              [Monster:19] [Event:20] [Shop:21]\n";
    std::cout << "                    \\       |       /\n";
    std::cout << "                [Rest:16] [Elite:17] [Monster:18]\n";
    std::cout << "                    /       |       \\\n";
    std::cout << "               [Event:13] [Monster:14] [Shop:15]\n";
    std::cout << "                    \\       |       /\n";
    std::cout << "               [Elite:10] [Monster:11] [Shop:12]\n";
    std::cout << "                    /       |       \\\n";
    std::cout << "                [Monster:7] [Event:8] [Rest:9]\n";
    std::cout << "                    \\       |       /\n";
    std::cout << "                 [Shop:4] [Monster:5] [Event:6]\n";
    std::cout << "                    /       |       \\\n";
    std::cout << "                [Monster:1] [Event:2] [Monster:3]\n";
    std::cout << "                         \\    |    /\n";
    std::cout << "                              [Start:0]\n\n";

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
        return "이벤트";
    case ENodeType::Rest:
        return "휴식";
    case ENodeType::Boss:
        return "보스";
    default:
        return "알 수 없음";
    }
}
