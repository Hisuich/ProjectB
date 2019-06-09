#include "Item.h"

Item::Item(long id, PointXYZ position)
	: DynamicObject(id, position)
{
	this->name = "Item";
	this->interactable = true;
}

Item::Item(long id)
	: Item(id, PointXYZ(0,0,0))
{
}

Item::Item()
{
	this->name = "Item";
	this->interactable = true;
}

