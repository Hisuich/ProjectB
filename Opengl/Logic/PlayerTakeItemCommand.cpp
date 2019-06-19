#include "PlayerTakeItemCommand.h"

#include "../Objects/Item.h"
#include "../Core/OpenGLApp.h"
#include "../Objects/Player.h"
#include "../Objects/Storage.h"

PlayerTakeItemCommand::PlayerTakeItemCommand(Item* item)
{
	this->obj = item;
}

PlayerTakeItemCommand::PlayerTakeItemCommand(Storage* storage)
{
	this->obj = storage;
}

void PlayerTakeItemCommand::Update(float dt)
{
	if (this->obj->name == "Item")
		this->mainApp->player->takeItem((Item*)this->obj);
	if (this->obj->name == "Storage")
	{
		this->mainApp->player->takeItem(((Storage*)this->obj)->storagedItem);
		((Storage*)this->obj)->storagedItem = nullptr;
	}
	isCompleted = true;
}