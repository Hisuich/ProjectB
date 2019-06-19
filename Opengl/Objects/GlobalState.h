#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <fstream>

class DynamicObject;
class Item;

class GlobalState
{
public:
	static std::string fileName;
	static std::vector<long long> playerInventory;
	static std::map<long long, std::vector<DynamicObject*>> lvl1ZoneObjects;

public:

	static void save();
	static void load();
	static void init();
	static void remove();

	static void setMapObjects(long long mapId, std::vector<DynamicObject*> objects);
	static void setPlayerInventory(std::vector<Item*> items);
};