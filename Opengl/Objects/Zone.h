#pragma once

#include "Direction.h"

#include "Player.h"
#include "Map.h"

class Zone
{
public:
	Map* activeMap;
	vector<vector<Map*>> maps;
	string zoneName;
	Player* player;

public:
	Zone(string zoneName, Player* player);

	void addMap(Map* map);


	void addMapTo(Map* first, Map* second, Direction direction);
 
};