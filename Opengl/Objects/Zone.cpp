#include "Zone.h"

Zone::Zone(string zoneName, Player* player)
{
	this->zoneName = zoneName;
	this->player = player;
}

void Zone::load(string fileName)
{
	ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) throw "File not found";
	ifs >> zoneRow >> zoneCol;
	int zoneSize = zoneRow * zoneCol;
	this->zone = new int[zoneSize];
	for (int i = 0; i < zoneSize; i++)
	{
		ifs >> zone[i];
	}
	init();
}

void Zone::init()
{
	for (int row = 0; row < zoneRow; row++)
	{
		for (int col = 0; col < zoneCol; col++)
		{
			std::cout << zone[(row * zoneRow) + col] << " ";
			if (zone[(row * zoneRow) + col] != 0)
			{
				addMap(new Map(zone[(row * zoneRow) + col]));
			}
		}
		std::cout << endl;
	}

	for (int row = 0; row < zoneRow; row++)
	{

		for (int col = 0; col < zoneCol; col++)
		{
			
			if (zone[(row * zoneRow) + col] != 0)
			{

				if (((row - 1) * zoneRow) + col >= 0 &&
					zone[((row - 1) * zoneRow) + col] != 0)
				{
					std::cout << endl << "UP" << endl << (row * zoneRow) + col << " "
						<< ((row - 1) * zoneRow) + col << endl;
					addMapTo(zone[(row * zoneRow) + col], zone[((row - 1) * zoneRow) + col], UP);
				}

				if ((row * zoneRow) + col + 1 < (row * zoneRow) + zoneCol &&
					zone[(row * zoneRow) + col + 1] != 0)
				{
					std::cout << endl << "RIGHT" << endl << (row * zoneRow) + col << " " << (row * zoneRow) + col + 1 << endl;
					addMapTo(zone[(row * zoneRow) + col], zone[(row * zoneRow) + col + 1], RIGHT);
				}

				if ((row * zoneRow) + col - 1 > (row * zoneRow) &&
					zone[(row * zoneRow) + col - 1] != 0)
				{
					std::cout << endl << "LEFT" << endl << (row * zoneRow) + col << " " << (row * zoneRow) + col - 1 << endl;
					addMapTo(zone[(row * zoneRow) + col], zone[(row * zoneRow) + col - 1], LEFT);
				}

				if (((row + 1)  * zoneRow ) + col < (zoneRow * zoneCol) &&
					zone[((row + 1) * zoneRow) + col] != 0)
				{
					std::cout << endl << "DOWN" << endl << (row * zoneRow) + col  << " "<< ((row + 1)  * zoneRow) + col << endl;
					addMapTo(zone[(row * zoneRow) + col], zone[((row + 1)  * zoneRow) + col], DOWN);
				}
			}
		}
		
	}
}

void Zone::addMap(Map * map)
{
	for (auto mp : maps)
	{
		if (mp.at(0)->id == map->id)
			return;
	}
	map->dynamicsObj.insert(map->dynamicsObj.begin(), player);
	maps.push_back(vector<Map*>({ map }));
}

Map* Zone::getMap(long long id)
{
	for (auto it : maps)
	{
		if (it.at(0)->id == id)
			return it.at(0);
	}
}

void Zone::addMapTo(Map * first, Map * second, Direction direction)
{ 
	for (auto &it : maps)
	{
		if (it.at(0)->id == first->id)
		{
			for (auto map : it)
			{
				if (map->id == second->id)
					return;
			}
			it.push_back(second);
			it.at(0)->addPass(second, direction);
		}

		if (it.at(0)->id == second->id)
		{
			for (auto map : it)
			{
				if (map->id == first->id)
					return;
			}
			it.push_back(first);
			it.at(0)->addPass(first, getOppositionalDir(direction));
		}
	}
}

void Zone::addMapTo(long long first, long long second, Direction direction)
{
	addMapTo(getMap(first), getMap(second), direction);
}
