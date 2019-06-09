#include "Map.h"

#include "Player.h"

Map::Map(const char* mapName)
{
	this->mapName = mapName;
}

Map::~Map()
{
	delete[] mapTyles;
	delete[] map;
}

Map::Map(int* map, int mapSize, int mapRow, const char* mapName)
{
	mapTyles = new long[mapSize];
	for (int i = 0; i < mapSize; i++)
	{
		mapTyles[i] = map[i];
	}
	this->mapRow = mapRow;
	this->mapName = mapName;
	this->mapSize = mapSize;
	init();
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
	mapSize = mapRow * mapCol;
	mapTyles = new long[mapSize];
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

}

vector<int> Map::findPass(Direction direction)
{
	vector<int> tiles = {};

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
	for (auto tile : this->findPass(direction))
	{
	GameObject thisPass = map[tile];
	Direction nextDirection = getOppositionalDir(direction);
	GameObject nextPass = nextMap->map[nextMap->findPass(nextDirection).at(tile % nextMap->findPass(nextDirection).size())];
	nextPass.setPosition(nextPass.getPosition().translate(direction % 2 == 1 ? 
								direction == 1 ? -32 : 32 : 0,
								direction % 2 == 0 ?
								direction == 2 ? 32 : -32 : 0));
	if (ID::getTileType(this->mapTyles[tile]) == 12)
		this->dynamicsObj.push_back(new Teleport(thisPass.getPosition(), nextPass.getPosition(), nextMap));
	if (ID::getTileType(this->mapTyles[tile]) == 13)
		this->dynamicsObj.push_back(new Teleport(thisPass.getPosition(), nextPass.getPosition(), nextMap, true));
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
			if (ID::getTileType(mapTyles[(i)* col + j]) == 10 || ID::getTileType(mapTyles[(i)* col + j]) == 11)
			{

			}
			if (ID::isDynamic((mapTyles[(i)* col + j]))) 
			{
				map[(i)* col + j] = GameObject(ID::setTileLvl(1000000000, ID::getTileLvl(mapTyles[(i)* col + j])), PointXYZ((j)*tyleSize, (mapRow - i)*tyleSize, 0));
				DynamicObject* tempObj = ID::getDynamicObject(mapTyles[(i)* col + j]);
				tempObj->id = mapTyles[(i)* col + j];
				tempObj->setPosition((j)*tyleSize, (mapRow - i)*tyleSize, 0);
				dynamicsObj.push_back(tempObj);
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
		((Player*)dynamicsObj.at(0))->eventProcessor->AddCommand(new TeleportCommand(
			sender,
			(Teleport*)target));
	}

}

