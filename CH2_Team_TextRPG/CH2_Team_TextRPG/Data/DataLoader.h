#pragma once

const std::string INIT_FILE_PATH = "../Script/ScriptList.json";

const std::string DATA_CATEGORY_ITEM = "Item";
const std::string DATA_CATEGORY_ITEM_CONSUMABLE = "Consumable";
const std::string DATA_CATEGORY_ITEM_EQUIPMENT = "Equipment";

const std::string DATA_CATEGORY_MONSTER = "Monster";

const std::string DATA_CATEGORY_MAP = "Map";

class DataLoader
{
	friend class GameInstance;

private:
	static bool LoadInitialGameData();
};

