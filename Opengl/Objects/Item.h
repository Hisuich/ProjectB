#ifndef ITEM
#define ITEM

#include "DynamicObject.h"

class Item : public DynamicObject
{
public:

	Item(long id, PointXYZ position);
	Item(long id);
	Item();
};

#endif
