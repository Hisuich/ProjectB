#include "TeleportCommand.h"

#include "../Objects/Teleport.h"
#include "../Core/OpenGLApp.h"

TeleportCommand::TeleportCommand(DynamicObject* obj, Teleport* teleport)
	: Command(obj)
{
	this->teleport = teleport;
}

void TeleportCommand::Update(float dt)
{
	if (teleport->locked)
	{
		mainApp->eventProcessor->AddCommand(new TextCommand("Locked"));
	}
	else
	{
		mainApp->ChangeMap(teleport->destinationMap, teleport->destinationPosition.x, teleport->destinationPosition.y);
	}

	isCompleted = true;
}