#pragma once
#include "DataTable.h"

struct MonsterData
{
    std::string Name;
    uint32_t Id;
    uint32_t Level;
    uint32_t HP;
    uint32_t MP;
    uint32_t Attack;
    uint32_t Defence;
    uint32_t Exp;
    std::string DropItemName;
    int DropItemPrice;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MonsterData,
    Name, Id, Level, HP, MP, Attack, Defence, Exp, DropItemName, DropItemPrice);

class MonsterDataTable final : public BaseDataTable
{
private:
    MonsterDataTable() {};
public:
    ~MonsterDataTable();
    static MonsterDataTable& GetInstance();
    const MonsterData* FindMonsterDataByName(const std::string& Name) const;
    const MonsterData* FindMonsterDataById(uint32_t Id) const;
protected:
    virtual void ParseData(const json& InData) override;
private:
    std::vector<const MonsterData*> MonsterDatas;
    std::unordered_map<std::string, const MonsterData*> NameMap;
    std::unordered_map<uint32_t, const MonsterData*> IndexMap;
};

inline const MonsterData* FindMonsterDataByName(const std::string& Name)
{
    return MonsterDataTable::GetInstance().FindMonsterDataByName(Name);
}
inline const MonsterData* FindMonsterDataById(uint32_t Id)
{
    return MonsterDataTable::GetInstance().FindMonsterDataById(Id);
}