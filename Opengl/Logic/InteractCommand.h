#ifndef INTERACT_COMMAND
#define INTERACT_COMMAND


#include "Command.h"
#include "../Objects/Map.h"
#include "../Objects/Player.h"

class InteractCommand : public Command
{
public:
	GameObject* interactableObject = nullptr;

	InteractCommand(DynamicObject* dynObject, Direction direction);

	void Update(float dt) override;
};

#endif
