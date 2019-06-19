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
	int* zone;
	int zoneRow;
	int zoneCol;

public:
	Zone(string zoneName, Player* player);

	void load(string fileName);
	void init();

	Map* getMap(long long id);

	void addMap(Map* map);

	void addMapTo(Map* first, Map* second, Direction direction);
	void addMapTo(long long first, long long second, Direction direction);
 
};