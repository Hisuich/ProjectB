#ifndef ID_HEADER
#define ID_HEADER

#include <iostream>
#include <string>
#include <map>
#include "../Graphics/BMP.h"
#include "Direction.h"

class DynamicObject;
#include "Item.h";
#include "Teleport.h";

class ID {

private:
	static std::string ResourcesPath;
	static std::map<long, BMP*> idMapTile;
	static std::map<long, BMP*> idDynamicObjects;
	static std::map<long, string> objectDescription;


public:

	static string getObjectDescription(long id);
	static BMP* getSprite(long id);
	static bool isMapTyleSolid(long id);
	static int getTileType(long id);
	static Direction getTileDirection(long id);
	static bool isTileInteractable(long id);
	static bool isDynamic(long id);
	static int getTileLvl(long id);
	static long setTileLvl(long id, int lvl);
	static DynamicObject* getDynamicObject(long id);
};

#endif