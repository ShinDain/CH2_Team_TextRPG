#include "pch.h"
#include "MonsterDataTable.h"

MonsterDataTable& MonsterDataTable::GetInstance()
{
    static MonsterDataTable Instance;
    return Instance;
}

// JSON 한 항목을 파싱해서 세 컨테이너에 등록
void MonsterDataTable::ParseData(const json& InData)
{
    MonsterData* data = new MonsterData(InData.get<MonsterData>());
    MonsterDatas.push_back(data);
    NameMap[data->Name] = data;
    IndexMap[data->Id] = data;
}

// 이름으로 검색
const MonsterData* MonsterDataTable::FindMonsterDataByName(const std::string& Name) const
{
    auto it = NameMap.find(Name);
    if (it == NameMap.end())
        return nullptr;
    return it->second;
}

// ID로 검색
const MonsterData* MonsterDataTable::FindMonsterDataById(uint32_t Id) const
{
    auto it = IndexMap.find(Id);
    if (it == IndexMap.end())
        return nullptr;
    return it->second;
}

MonsterDataTable::~MonsterDataTable()
{
    for (auto& data : MonsterDatas)
    {
        delete data;
    }
}