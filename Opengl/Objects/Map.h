#pragma once

#include "ID.h"
#include "Teleport.h"

class Map
{
private:
	

	int mapSize;

	int mapRow;
	int mapCol;

	long* mapTyles = nullptr;
	GameObject* map = nullptr;

public:
	const int tyleSize = 32;
	const char* mapName;
	std::vector<DynamicObject*> dynamicsObj = {};

public:
	Map(int* map, int mapSize, int mapRow, const char* mapName);

	Map(const char* mapName);
	~Map();

	GameObject* getTyle(PointXYZ position);
	DynamicObject* getDynamicObjectByPosition(PointXYZ position);
	bool removeDynamicObjectByPosition(PointXYZ position);
	void load(const char* fileName);

	vector<int> findPass(Direction direction);
	void addPass(Map* nextMap, Direction direction);

	void init();
	void display();
	void removeDynamics();
	void populateDynamics();
	void onInteraction(DynamicObject* sender, GameObject* target);

};

