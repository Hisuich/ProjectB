#pragma once

#include "Command.h"

class Item;

class PlayerTakeItemCommand : public Command
{
public:
	
	PlayerTakeItemCommand(Item* item);

	void Update(float dt) override;
};
