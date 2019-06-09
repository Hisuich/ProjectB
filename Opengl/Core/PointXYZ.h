#ifndef POINTXYZ
#define POINTXYZ

class PointXYZ {
public:
	PointXYZ();
	PointXYZ(int x, int y, int z);

	PointXYZ* translate(int offsetX, int offsetY);

	int x;
    int y;
	int z;

};
#endif
