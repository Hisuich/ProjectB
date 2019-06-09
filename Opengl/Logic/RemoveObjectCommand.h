#pragma once

#include "Command.h"
#include "../Core/PointXYZ.h"

class RemoveObjectCommand : public Command
{

public:

	RemoveObjectCommand(DynamicObject* obj);
	RemoveObjectCommand(PointXYZ position);

	void Update(float dt) override;
};