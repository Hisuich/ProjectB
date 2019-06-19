#include "ID.h"

/*
XXSDMMLLYY
XX - Type of Object
S - Solid or not Solid. Always 0 - if not solid and 1 if solid.
D - direction
MM - Condition of mind
LL - Level
YY - directly the object

XXX:
10 - floor
11 - wall
12 - pass
13 - locked pass
14 - part of table
20 - vase
21 - key. must be same with locked pass


S:
0 - not solid
1-9 - solid

MM:

LL:
00 - hall
*/
std::string ID::ResourcesPath = "Resources/sprites/";
std::string ID::ResourcesMapPath = "Resources/Maps/";
std::map<long long, BMP*> ID::idMapTile = { 
											{0, new BMP(ResourcesPath + "empty.bmp")},
											{1000000000, new BMP(ResourcesPath + "hall_floor_tyle.bmp")},
											{1110000000, new BMP(ResourcesPath + "hall_wall.bmp")},
											{1203000000, new BMP(ResourcesPath + "Nothing.bmp")},
											{1201000000, new BMP(ResourcesPath + "Nothing.bmp")},
											{1301000000, new BMP(ResourcesPath + "Nothing.bmp")},
											{1303000000, new BMP(ResourcesPath + "Nothing.bmp")},
											{1410000100, new BMP(ResourcesPath + "lvl1_table_down_left.bmp")},
											{1410000101, new BMP(ResourcesPath + "lvl1_table_down_right.bmp")},
											{1410000102, new BMP(ResourcesPath + "lvl1_table_mid_left.bmp")},
											{1410000103, new BMP(ResourcesPath + "lvl1_table_mid_right.bmp")},
											{1410000104, new BMP(ResourcesPath + "lvl1_table_up_left.bmp")},
											{1410000105, new BMP(ResourcesPath + "lvl1_table_up_right.bmp")},
											{1413000101, new BMP(ResourcesPath + "lvl1_horizontal_table_down_left.bmp")},
											{1413000103, new BMP(ResourcesPath + "lvl1_horizontal_table_down_mid.bmp")},
											{1413000105, new BMP(ResourcesPath + "lvl1_horizontal_table_down_right.bmp")},
											{1413000100, new BMP(ResourcesPath + "lvl1_horizontal_table_up_left.bmp")},
											{1413000102, new BMP(ResourcesPath + "lvl1_horizontal_table_up_mid.bmp")},
											{1413000104, new BMP(ResourcesPath + "lvl1_horizontal_table_up_right.bmp")},
											{1510000100, new BMP(ResourcesPath + "lvl1_clown_picture.bmp")},
											{2010000000, new BMP(ResourcesPath + "vase.bmp")},
											{2111000000, new BMP(ResourcesPath + "key.bmp")},
											{3010000000, new BMP(ResourcesPath + "main_small_table_key.bmp")},
											{3110000000, new BMP(ResourcesPath + "main_small_table.bmp")},
											{3200000000, new BMP("Resources/Enemies/Enemy_lvl1_1.bmp")},
											{1000000100, new BMP(ResourcesPath + "lvl1_floor.bmp")},
											{1110000100, new BMP(ResourcesPath + "lvl1_wall.bmp")}
											};

std::map<long long, BMP*> ID::idDynamicObjects = {
	{2010000000, new BMP(ResourcesPath + "vase.bmp")},
	{2111000000, new BMP(ResourcesPath + "key.bmp")},
	{3200000000, new BMP("Resources/Enemies/Enemy_lvl1_1.bmp")}

};

std::map<long long, string> ID::objectDescription =
{
	{1110000000, "Just a wall. But it has strange color" },
	{1110000100, "What a big rock. I have never seen the wall like this before."}
};

std::map<long long, string> ID::idMaps = 
{
	{1000, ResourcesMapPath + "main_hall.map"},
	{1001, ResourcesMapPath + "main_hall_cont.map"},
	{1002, ResourcesMapPath + "lvl1_hall_1.map"},
	{2001, ResourcesMapPath + "lvl1_corridor_1.map"},
	{3001, ResourcesMapPath + "lvl1_bigroom_1.map"}
};

std::map<long long, std::vector<Observer*>> ID::observersById =
{
	{1303000000, std::vector<Observer*>({new ItemLockedObserver(2111000000)}) },
	{1301000000, std::vector<Observer*>({new ItemLockedObserver(2111000000)}) }
};

std::map<long long, long long> ID::storageItems =
{
	{3010000000, 2111000000}
};

DynamicObject* ID::getDynamicObject(long long id)
{
	DynamicObject* obj;
	int idShort = getTileType(id);
	if (idShort == 30)
	{
		obj = new Storage(id);
		((Storage*)obj)->storagedItem = getStorageItem(id);
		cout << ((Storage*)obj)->storagedItem->id;
		return obj;
	}
	if (idShort == 32)
	{
		obj = new Enemy(id);
		return obj;
	}
	if (idShort >= 20 && idShort < 30)
	{
		obj = new Item();
		obj->id = id;
		obj->sprite = getSprite(id);
			return obj;
	}
	return new DynamicObject(id);
}

Item* ID::getStorageItem(long long id)
{
	for (auto storageItem : storageItems)
	{
		if (storageItem.first == id)
			return new Item(storageItem.second);
	}
}

string ID::getObjectDescription(long long id)
{
	for (auto obj : objectDescription)
	{
		if (obj.first == id)
			return obj.second;
	}
	return "Nothing Interesting";
}

bool ID::isMapTyleSolid(long long id)
{
	return id && (id / 10000000) % 100 % 10;
}

BMP* ID::getSprite(long long id)
{
	for (auto beg = begin(idMapTile); beg != end(idMapTile); beg++)
	{
		if (id == beg->first)
			return idMapTile.at(id);
	}
	return idMapTile.at(0);
}

int ID::getTileType(long long id)
{
	return id / 100000000;
}
Direction ID::getTileDirection(long long id)
{
	if (id) return Direction((id / 1000000) % 1000 % 100 % 10);
	else return Direction(0);
}

bool ID::isTileInteractable(long long id)
{
	if (id / 100000000 == 11) return true;
	if (id / 1000000000 == 1) return false;
	else return true;
}

bool ID::isDynamic(long long id)
{
	if (idDynamicObjects.find(id) != idDynamicObjects.end())
		return true;
	if (ID::getTileType(id) > 13)
		return true;
	else
		return false;
}

int ID::getTileLvl(long long id)
{
	return (id % 1000000) / 100;
}

long long ID::setTileType(long long id, long long type)
{
	long long temp = id / 100000000;
	long long t_id = id - (temp * 100000000);
	t_id = type * 100000000 + t_id;

	return t_id;
}

long long ID::setTileLvl(long long id, int lvl)
{
	return id + lvl * 100;
}

int ID::getTileNumber(long long id)
{
	return id % 10000000;
}

void ID::setObservers(GameObject* object)
{
	for (auto pair : observersById)
	{
		if (pair.first == object->id)
		{
			cout << "I'm here";
			object->addObservers(pair.second, object);
		}
	}
}

string ID::getMapPath(long long id)
{
	for (auto map : idMaps)
	{
		if (map.first == id)
		{
			std::cout << map.second << " " << endl;
			return map.second;
		}
	}
	std::cout << "What happen" << endl;
	return "";
}
