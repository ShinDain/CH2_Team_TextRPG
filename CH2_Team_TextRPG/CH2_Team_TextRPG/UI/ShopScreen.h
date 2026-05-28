#pragma once

#include <string>
#include <vector>

struct ItemData;
class Player;

class ShopScreen
{
public:
	static void Draw(
		Player* MainPlayer,
		const std::vector<const ItemData*>& ShopItems,
		const ItemData* SelectedItem,
		const std::string& LastMessage,
		bool bDetailMode
	);
};
