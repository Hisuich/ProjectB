#include "Zone.h"

Zone::Zone(string zoneName, Player* player)
{
	this->zoneName = zoneName;
	this->player = player;
}

void Zone::addMap(Map * map)
{
	map->dynamicsObj.insert(map->dynamicsObj.begin(), player);
	maps.push_back(vector<Map*>({ map }));
}

void Zone::addMapTo(Map * first, Map * second, Direction direction)
{
	for (auto &it : maps)
	{
		if (it.at(0)->mapName == first->mapName)
		{
			it.push_back(second);
			it.at(0)->addPass(second, direction);
		}

		if (it.at(0)->mapName == second->mapName)
		{
			it.push_back(first);
			it.at(0)->addPass(first, getOppositionalDir(direction));
		}
	}

}
