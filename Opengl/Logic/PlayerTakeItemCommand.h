#pragma once

#include "Command.h"

class Item;
class Storage;

class PlayerTakeItemCommand : public Command
{
public:
	
	PlayerTakeItemCommand(Item* item);
	PlayerTakeItemCommand(Storage* storage);

	void Update(float dt) override;
};
