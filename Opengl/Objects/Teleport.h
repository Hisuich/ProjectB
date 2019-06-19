#ifndef TELEPORT
#define TELEPORT

#include "DynamicObject.h"
#include "../Logic/TeleportCommand.h"
#include "../Logic/ItemLockedObserver.h"
#include "Item.h"

class Map;

class Teleport : public DynamicObject
{
public:
	PointXYZ destinationPosition;
	Map* destinationMap = nullptr;
	bool locked = false;

public:
	Teleport();
	Teleport(long long id, PointXYZ currentPosition, PointXYZ destinationPosition, Map* destinationMap, bool locked);
	Teleport(long long id, PointXYZ currentPosition, PointXYZ destinationPosition, Map* destinationMap);


	void update(float dt) override;
	bool openTerms();
};

#endif