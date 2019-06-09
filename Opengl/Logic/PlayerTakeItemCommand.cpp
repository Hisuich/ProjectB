#include "PlayerTakeItemCommand.h"

#include "../Objects/Item.h"
#include "../Core/OpenGLApp.h"
#include "../Objects/Player.h"

PlayerTakeItemCommand::PlayerTakeItemCommand(Item* item)
{
	this->obj = item;
}

void PlayerTakeItemCommand::Update(float dt)
{
	this->mainApp->player->takeItem((Item*)this->obj);
	isCompleted = true;
}