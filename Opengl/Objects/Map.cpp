#include "Map.h"

#include "Player.h"
#include "../Core/OpenGLApp.h"

Map::Map(const char* mapName)
{
	this->mapName = mapName;
}

Map::Map(int* map, int mapSize, int mapRow, const char* mapName)
{
	mapTyles = new long long[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		mapTyles[i] = map[i];
	}
	this->mapRow = mapRow;
	this->mapName = mapName;
	this->mapSize = mapSize;
	init();
}

Map::Map(long long id)
{
	this->id = id;
	load(ID::getMapPath(id).c_str());
}

Map::~Map()
{
	delete[] mapTyles;
	delete[] map;
}

GameObject* Map::getTyle(PointXYZ position)
{
	int col = mapSize / mapRow;
	if (position.x == 0) position.x = 1;
	if (position.y == 0) position.y = 1;
	int tyleRow = floor(position.y / tyleSize);
	int tyleCol = floor(position.x / tyleSize);
	if (tyleRow > mapRow || tyleRow <= 0 || tyleCol >= col || tyleCol <= 0) return new GameObject(0l, PointXYZ(tyleCol*tyleSize, tyleRow*tyleSize, 0));
	return &map[(mapRow - tyleRow) * col + tyleCol];
	}

void Map::load(const char * fileName)
{
	ifstream ifs(fileName, std::ios::in | std::ios::binary);
	if (!ifs.is_open()) throw "File not found";
	ifs >> mapRow >> mapCol;
	cout << " ROW: " << mapRow << " COL: " << mapCol;
	mapSize = mapRow * mapCol;
	mapTyles = new long long[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		ifs >> mapTyles[i];
	}
	init();
}

void Map::display()
{
	int col = mapSize / mapRow;
	for (int i = 0; i < mapRow; i++)
	{
		for (int j = 0; j < col; j++)
		{
			map[i * col + j].drawGameObject();
		}

	}
}

void Map::removeDynamics()
{
	this->dynamicsObj.clear();
}

void Map::populateDynamics()
{
	int col = mapSize / mapRow;
	for (int i = 0; i < mapRow; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (ID::isDynamic((mapTyles[(i)* col + j])))
			{
				DynamicObject* tempObj = ID::getDynamicObject(mapTyles[(i)* col + j]);
				tempObj->id = mapTyles[(i)* col + j];
				tempObj->setPosition((j)*tyleSize, (mapRow - i)*tyleSize, 0);
				dynamicsObj.push_back(tempObj);
			}
		}
	}
}

vector<long long> Map::findPass(Direction direction)
{
	vector<long long> tiles = {};

	for (int tile = 0; tile < this->mapSize; tile++)
	{
		if (ID::getTileType(this->mapTyles[tile]) == 12 ||
			ID::getTileType(this->mapTyles[tile]) == 13)
		{
			
			if (ID::getTileDirection(this->mapTyles[tile]) == direction)
				
				tiles.push_back(tile);
		}
	}
	return tiles;
}

void Map::addPass(Map * nextMap, Direction direction)
{
	cout << " SIZE " << this->findPass(direction).size();
	for (int tile = 0; tile < this->findPass(direction).size(); tile++)
	{
		cout << " THIS: " << mapTyles[this->findPass(direction).at(tile)];
		cout << " NEXT: " << nextMap->id << mapTyles[nextMap->findPass(getOppositionalDir(direction)).at(tile)];
		/*for (int i = 0; i < nextMap->mapRow; i++)
		{
			cout << endl;
			for (int j = 0; j < nextMap->mapCol; j++)
				cout << nextMap->mapTyles[i * nextMap->mapRow + j] << " ";
			cout << endl;
		}*/
	GameObject thisPass = map[this->findPass(direction).at(tile)];
	Direction nextDirection = getOppositionalDir(direction);
	GameObject nextPass = nextMap->map[nextMap->findPass(nextDirection).at(tile)];
	nextPass.setPosition(nextPass.getPosition().translate(
									direction == 1 ? 
								-32 : direction == 3 ? 32 : 0, 
									direction == 2 ?
								32 : direction == 4 ? -32 : 0));
	if (ID::getTileType(this->mapTyles[this->findPass(direction).at(tile)]) == 12)
		this->dynamicsObj.push_back(new Teleport(mapTyles[this->findPass(direction).at(tile)], thisPass.getPosition(), nextPass.getPosition(), nextMap));
	if (ID::getTileType(this->mapTyles[this->findPass(direction).at(tile)]) == 13)
		this->dynamicsObj.push_back(new Teleport(mapTyles[this->findPass(direction).at(tile)], thisPass.getPosition(), nextPass.getPosition(), nextMap, true));
	}

}

void Map::init()
{
	map = new GameObject[mapSize];
	int col = mapSize / mapRow;
	for (int i = 0; i < mapRow; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << mapTyles[(i)* col + j] << " ";
			if (ID::getTileType(mapTyles[(i)* col + j]) == 10 || ID::getTileType(mapTyles[(i)* col + j]) == 11)
			{

			}
			if (ID::isDynamic((mapTyles[(i)* col + j]))) 
			{
				map[(i)* col + j] = GameObject(ID::setTileLvl(1000000000, ID::getTileLvl(mapTyles[(i)* col + j])), PointXYZ((j)*tyleSize, (mapRow - i)*tyleSize, 0));
			}
			else {
			map[(i) * col + j] = GameObject(mapTyles[i * col + j], PointXYZ((j)*tyleSize, (mapRow - i)*tyleSize, 0));
			}
		}
	}
	populateDynamics();
}

DynamicObject* Map::getDynamicObjectByPosition(PointXYZ position)
{
	for (auto dyn = this->dynamicsObj.begin() + 1; dyn != this->dynamicsObj.end(); dyn++)
	{
		if ((*dyn)->getPosition().x <= position.x && (*dyn)->getPosition().x + (*dyn)->getWidth() >= position.x
			&& (*dyn)->getPosition().y <= position.y && (*dyn)->getPosition().y + (*dyn)->getHeight() >= position.y)
		{
			return (*dyn);
		}
	}
	return nullptr;
}

bool Map::removeDynamicObjectByPosition(PointXYZ position)
{
	for (auto dyn = this->dynamicsObj.begin() + 1; dyn != this->dynamicsObj.end(); dyn++)
	{
		if ((*dyn)->getPosition().x <= position.x && (*dyn)->getPosition().x + (*dyn)->getWidth() >= position.x
			&& (*dyn)->getPosition().y <= position.y && (*dyn)->getPosition().y + (*dyn)->getHeight() >= position.y)
		{
			dynamicsObj.erase(dyn);
			return true;
		}
	}
	return false;
}

void Map::onInteraction(DynamicObject* sender, GameObject* target)
{
	if (target->name == "Teleport")
	{
		((Player*)dynamicsObj.at(0))->mainApp->eventProcessor->AddCommand(new TeleportCommand(
			sender,
			(Teleport*)target));
	}

}

