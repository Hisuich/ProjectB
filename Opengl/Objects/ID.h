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
#include "Storage.h";
#include "Enemy.h"

class ID {

private:
	static std::string ResourcesPath;
	static std::string ResourcesMapPath;
	static std::map<long long, BMP*> idMapTile;
	static std::map<long long, BMP*> idDynamicObjects;
	static std::map<long long, string> objectDescription;
	static std::map<long long, string> idMaps;
	static std::map<long long, std::vector<Observer*>> observersById;
	static std::map<long long, long long> storageItems;


public:

	static string getObjectDescription(long long id);
	static BMP* getSprite(long long id);
	static bool isMapTyleSolid(long long id);
	static int getTileType(long long id);
	static Direction getTileDirection(long long id);
	static bool isTileInteractable(long long id);
	static bool isDynamic(long long id);
	static int getTileLvl(long long id);
	static int getTileNumber(long long id);
	static long long setTileLvl(long long id, int lvl);
	static long long setTileType(long long id, long long type);
	static DynamicObject* getDynamicObject(long long id);
	static void setObservers(GameObject* object);
	static Item* getStorageItem(long long id);
	static string getMapPath(long long id);
};

#endif