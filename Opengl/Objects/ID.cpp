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
std::map<long, BMP*> ID::idMapTile = { 
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
											{1000000100, new BMP(ResourcesPath + "lvl1_floor.bmp")},
											{1110000100, new BMP(ResourcesPath + "lvl1_wall.bmp")}
											};

std::map<long, BMP*> ID::idDynamicObjects = {
	{2010000000, new BMP(ResourcesPath + "vase.bmp")},
	{2111000000, new BMP(ResourcesPath + "key.bmp")}

};

std::map<long, string> ID::objectDescription =
{
	{1110000000, "Just a wall. But it has strange color" },
	{1110000100, "What a big rock. I have never seen the wall like this before."}
};

DynamicObject* ID::getDynamicObject(long id)
{
	DynamicObject* obj;
	int idShort = getTileType(id);
	if (idShort >= 20)
	{
		obj = new Item();
		obj->sprite = getSprite(id);
			return obj;
	}
	return new DynamicObject(id);
}

string ID::getObjectDescription(long id)
{
	for (auto obj : objectDescription)
	{
		if (obj.first == id)
			return obj.second;
	}
	return "Nothing Interesting";
}

bool ID::isMapTyleSolid(long id)
{
	return id && (id / 10000000) % 100 % 10;
}

BMP* ID::getSprite(long id)
{
	for (auto beg = begin(idMapTile); beg != end(idMapTile); beg++)
	{
		if (id == beg->first)
			return idMapTile.at(id);
	}
	return idMapTile.at(0);
}

int ID::getTileType(long id)
{
	return id / 100000000;
}
Direction ID::getTileDirection(long id)
{
	if (id) return Direction((id / 1000000) % 1000 % 100 % 10);
	else return Direction(0);
}

bool ID::isTileInteractable(long id)
{
	if (id / 100000000 == 11) return true;
	if (id / 1000000000 == 1) return false;
	else return true;
}

bool ID::isDynamic(long id)
{
	if (idDynamicObjects.find(id) != idDynamicObjects.end())
		return true;
	if (ID::getTileType(id) > 13)
		return true;
	else
		return false;
}

int ID::getTileLvl(long id)
{
	return (id % 1000000) / 100;
}

long ID::setTileLvl(long id, int lvl)
{
	return id + lvl * 100;
}
