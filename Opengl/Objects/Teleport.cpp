#include "Teleport.h"

#include "ID.h"

Teleport::Teleport()
	: DynamicObject::DynamicObject()
{
	
	this->sprite = new BMP("Resources/sprites/Nothing.bmp");
	
	this->interactable = true;
	
}

Teleport::Teleport(long long id, PointXYZ currentPosition, PointXYZ destinationPosition, Map * destinationMap, bool locked)
	: Teleport(id, currentPosition, destinationPosition, destinationMap)
{
	this->locked = locked;

	ID::setObservers(this);
}

Teleport::Teleport(long long id, PointXYZ currentPosition, PointXYZ destinationPosition, Map * destinationMap)
	: Teleport()
{
	this->id = id;
	this->name = "Teleport";
	this->position = currentPosition;
	this->destinationPosition = destinationPosition;
	this->destinationMap = destinationMap;

	
}

bool Teleport::openTerms()
{
	
}

void Teleport::update(float dt)
{
	DynamicObject::update(dt);
}
