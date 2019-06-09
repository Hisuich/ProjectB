#pragma once

#include "Command.h"

#include "TextCommand.h"

class Teleport;
class Map;

class TeleportCommand : public Command
{
public:
	Teleport* teleport = nullptr;

public:

	TeleportCommand(DynamicObject* obj, Teleport* teleport);

	void Update(float dt) override;
};
