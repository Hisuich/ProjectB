#include "ItemObserver.h"
#include "../Core/OpenGLApp.h"
#include "../Objects/Player.h"



ItemObserver::ItemObserver(Item* obj)
	: Observer::Observer(obj)
{
}

void ItemObserver::update(float dt)
{
	this->hasItem = this->mainApp->player->hasItem((Item*)obj);
}