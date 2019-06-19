#include "InteractCommand.h"

#include "../Core/OpenGLApp.h"

InteractCommand::InteractCommand(DynamicObject* dynObject, Direction direction) : Command(dynObject)
{
	this->obj = dynObject;
	int tileSize = mainApp->currentMap->tyleSize;
	interactableObject = mainApp->currentMap->getDynamicObjectByPosition(PointXYZ(
		dynObject->getPosition().x + (direction == LEFT ? -tileSize : direction == RIGHT ? tileSize : 0),
		dynObject->getPosition().y + (direction == DOWN ? -tileSize : direction == UP ? tileSize : 0), 0));
	if (interactableObject == nullptr)
		interactableObject = mainApp->currentMap->getTyle(PointXYZ(
			dynObject->getPosition().x + (direction == LEFT ? -tileSize : direction == RIGHT ? tileSize : 0),
			dynObject->getPosition().y + (direction == DOWN ? -tileSize : direction == UP ? tileSize : 0), 0));
}

void InteractCommand::Update(float dt) 
{
	cout << " NAME: " << interactableObject->name << " ID: " << interactableObject->id;
	if (interactableObject->interactable) {
		((Player*)obj)->onStaticInteraction(interactableObject);
		this->mainApp->currentMap->onInteraction(this->obj, interactableObject);
	}
	isCompleted = true;
}