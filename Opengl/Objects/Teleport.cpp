#include "Teleport.h"

Teleport::Teleport()
{
	this->sprite = new BMP("Resources/sprites/Nothing.bmp");
	this->name = "Teleport";
	this->interactable = true;
}

Teleport::Teleport(PointXYZ currentPosition, PointXYZ destinationPosition, Map * destinationMap, bool locked)
	: Teleport(currentPosition, destinationPosition, destinationMap)
{
	this->locked = locked;
	if (locked)
	{
		this->itemObs = new ItemObserver(new Item(2111000000));
		this->observers.push_back(itemObs);
		
	}
}

Teleport::Teleport(PointXYZ currentPosition, PointXYZ destinationPosition, Map * destinationMap)
{
	this->sprite = new BMP("Resources/sprites/Nothing.bmp");
	this->position = currentPosition;
	this->destinationPosition = destinationPosition;
	this->destinationMap = destinationMap;
	this->name = "Teleport";
	this->interactable = true;
}

bool Teleport::openTerms()
{
	return this->itemObs->hasItem;
}

void Teleport::update(float dt)
{
	DynamicObject::update(dt);
	if (this->locked)
	{
		this->locked = !openTerms();
	}
}
