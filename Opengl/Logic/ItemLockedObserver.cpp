#include "ItemLockedObserver.h"
#include "../Core/OpenGLApp.h"
#include "../Objects/Player.h"



ItemLockedObserver::ItemLockedObserver(long long keyId, Teleport* pass)
	: ItemLockedObserver::ItemLockedObserver(keyId)
{
	
	if (pass->name == "Teleport") 
	{
		this->obj = pass;
		cout << "DING DING DING MAZAFAKA";
	}
}

ItemLockedObserver::ItemLockedObserver(long long keyId)
{
	this->keyId = keyId;
}

void ItemLockedObserver::update(float dt)
{
	((Teleport*)this->obj)->locked = !this->mainApp->player->hasItem(keyId);
	cout << "LOCKED: " << ((Teleport*)this->obj)->locked;
}
