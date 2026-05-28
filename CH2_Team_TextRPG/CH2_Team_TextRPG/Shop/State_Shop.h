#pragma once

#include "Core/State.h"
#include <string>
#include <vector>

struct ItemData;

class State_Shop : public BaseState
{
public:
	State_Shop();

protected:
	virtual void Enter() override;
	virtual void Process() override;
	virtual void Exit() override;

private:
	std::vector<const ItemData*> ShopItems;
	std::string LastMessage;
};
