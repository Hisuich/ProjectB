#include "Storage.h"
#include "ID.h"

Storage::Storage(long long id, PointXYZ position, Item* storageItem)
	: DynamicObject(id, position)
{
	this->name = "Storage";
	this->storagedItem = storageItem;
}

Storage::Storage(long long id, PointXYZ position, long long storageItemId)
	: Storage(id, position, new Item(storageItemId))
{
	
}

Storage::Storage(long long id)
	: Storage(id, PointXYZ(0, 0, 0), nullptr)
{

}

bool Storage::isEmpty()
{
	return this->storagedItem == nullptr;
}

void Storage::update(float dt)
{
	if (isEmpty())
	{
		this->id = ID::setTileType(this->id, 31);
		this->sprite = ID::getSprite(this->id);
	}
}