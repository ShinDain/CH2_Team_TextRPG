#include "pch.h"
#include "RecordManager.h"
#include "Map/MapManager.h" 


RecordManager::RecordManager()
{
	Initialize();
}

RecordManager& RecordManager::GetInstance()
{
	static RecordManager Instance;
	return Instance;
}

void RecordManager::Initialize()
{
	MonsterKills = 0;
	EliteKills = 0;
	NodeVisitCounts.clear();
}

void RecordManager::IncrementMonsterKills()
{
	MonsterKills++;
}

void RecordManager::IncrementEliteKills()
{
	EliteKills++;
}

void RecordManager::AddNodeVisitCount(ENodeType Type)
{
	// map에 해당 키가 없으면 0으로 초기화 후 1 증가, 있으면 기존 값에서 1 증가
	NodeVisitCounts[Type]++;
}

int RecordManager::GetNodeVisitCount(ENodeType Type) const
{
	auto iter = NodeVisitCounts.find(Type);
	if (iter != NodeVisitCounts.end())
	{
		return iter->second;
	}
	return 0; 
}

int RecordManager::GetTotalNodeVisits() const
{
	int Total = 0;
	for (const auto& pair : NodeVisitCounts)
	{
		Total += pair.second;
	}
	return Total;
}