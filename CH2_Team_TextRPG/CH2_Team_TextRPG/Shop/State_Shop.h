#pragma once

#include "Core/State.h"
#include <string>
#include <vector>

struct ItemData;
class Player;

class State_Shop : public BaseState
{
public:
	State_Shop();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	enum class EShopScreenMode
	{
		ItemList,
		ItemDetail
	};

	void ProcessItemList(Player* MainPlayer);
	void ProcessItemDetail(Player* MainPlayer);
	const ItemData* GetSelectedItem() const;
	std::string TryBuyItem(Player* MainPlayer, int ItemIndex) const;

	std::vector<const ItemData*> ShopItems;
	std::string LastMessage;
	EShopScreenMode CurrentMode = EShopScreenMode::ItemList;
	int SelectedItemIndex = -1;
};
