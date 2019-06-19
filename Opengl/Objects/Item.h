#ifndef ITEM
#define ITEM

#include "DynamicObject.h"

class Item : public DynamicObject
{
public:

	Item(long long id, PointXYZ position);
	Item(long long id);
	Item();
};

#endif
