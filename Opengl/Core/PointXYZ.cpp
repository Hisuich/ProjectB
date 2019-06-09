#include "PointXYZ.h"

PointXYZ::PointXYZ()
{
	x = 0;
	y = 0;
	z = 0;
}

PointXYZ::PointXYZ(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

PointXYZ* PointXYZ::translate(int offsetX, int offsetY)
{
	this->x += offsetX;
	this->y += offsetY;
	return this;
}
