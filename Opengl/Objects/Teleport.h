#ifndef TELEPORT
#define TELEPORT

#include "DynamicObject.h"
#include "../Logic/TeleportCommand.h"
#include "../Logic/ItemObserver.h"
#include "Item.h"

class Map;

class Teleport : public DynamicObject
{
public:
	PointXYZ destinationPosition;
	Map* destinationMap = nullptr;
	bool locked = false;
	ItemObserver* itemObs;

public:
	Teleport();
	Teleport(PointXYZ currentPosition, PointXYZ destinationPosition, Map* destinationMap, bool locked);
	Teleport(PointXYZ currentPosition, PointXYZ destinationPosition, Map* destinationMap);


	void update(float dt) override;
	bool openTerms();
};

#endif