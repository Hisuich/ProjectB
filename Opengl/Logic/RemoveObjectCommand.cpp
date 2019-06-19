#include "RemoveObjectCommand.h"

#include "../Core/OpenGLApp.h"
#include "../Objects/Map.h"

RemoveObjectCommand::RemoveObjectCommand(DynamicObject* obj)
{
	this->obj = obj;
}

RemoveObjectCommand::RemoveObjectCommand(PointXYZ position)
{
	this->obj = this->mainApp->currentMap->getDynamicObjectByPosition(position);
}

void RemoveObjectCommand::Update(float dt)
{
	if(this->obj != nullptr)
		this->mainApp->currentMap->removeDynamicObjectByPosition(obj->getPosition());
	isCompleted = true;
}

