#pragma once

#include "DynamicObject.h"
class Item;

class Storage : public DynamicObject
{
public:
	Item* storagedItem;

public:
	Storage(long long id, PointXYZ position, Item* storagedItem);
	Storage(long long id, PointXYZ position, long long storagedItemId);
	Storage(long long id);

	void update(float dt) override;
	bool isEmpty();
};