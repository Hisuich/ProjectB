#include "GlobalState.h"
#include "DynamicObject.h"
#include "Item.h"

std::string GlobalState::fileName = "save.sf";

std::vector<long long> GlobalState::playerInventory = 
{
	
};

std::map<long long, std::vector<DynamicObject*>> GlobalState::lvl1ZoneObjects =
{

};

void GlobalState::save()
{
	std::ofstream of(fileName);
	if (of.is_open())
	{
		of << "playerInventory" << std::endl;
		of << "{" << std::endl;

		for (auto item : playerInventory)
		{
			of << item << "" << std::endl;
		}

		of << "}" << std::endl;

		of << "lvl1ZoneObjects" << std::endl;
		of << "{" << std::endl;

		for (auto map : lvl1ZoneObjects)
		{
			of << map.first << std::endl;
			of << "{" << std::endl;
			for (auto object : map.second)
			{
				of << object->id << "" << std::endl;
				of << object->position.x << "" << std::endl;
				of << object->position.y << "" << std::endl;
			}
			of <<  "}" << std::endl;
		}

		of << "}" << std::endl;
	}
}

void GlobalState::load()
{
	std::ifstream ifs(fileName);
	if (ifs.is_open())
	{
		char* val = new char[256];
		while (ifs.getline(val, 256))
		{
			if (strcmp(val, "playerInventory") == 0)
			{
				ifs.getline(val, 256);
				while (ifs.getline(val, 256))
				{
					if (strcmp(val, "}") == 0)
					{
						break;
					}
					playerInventory.push_back(atoll(val));
				}
			}
			std::cout << val;
			if (strcmp(val, "lvl1ZoneObjects") == 0)
			{
				ifs.getline(val, 256);
				while (ifs.getline(val, 256))
				{
					if (strcmp(val, "}") == 0)
					{
						break;
					}
					long long mapId = atoll(val);
					std::vector<DynamicObject*> objId;
					ifs.getline(val, 256);
					while (ifs.getline(val, 256))
					{
						if (strcmp(val, "}") == 0)
						{
							break;
						}

						long long id = atoll(val);
						ifs.getline(val, 256);
						int x = atoi(val);
						ifs.getline(val, 256);
						int y = atoi(val);

						objId.push_back(new DynamicObject(id, PointXYZ(x, y, 0)));
					}

					lvl1ZoneObjects.insert(lvl1ZoneObjects.end(), { mapId, objId });
				}
			}
		}
	}
}

void GlobalState::init()
{
}

void GlobalState::remove()
{
}

void GlobalState::setMapObjects(long long mapId, std::vector<DynamicObject*> objects)
{

}

void GlobalState::setPlayerInventory(std::vector<Item*> inventory)
{

}