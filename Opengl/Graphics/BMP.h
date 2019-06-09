#ifndef BMP_IMAGE
#define BMP_IMAGE

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class BMP 
{

private:
	uint32_t height, width;
	uint16_t bitsPerPixel;
	vector<uint8_t> pixels;

public:

	string fileName;
	BMP(string filePath);
	vector<uint8_t> getPixels() { return this->pixels; }
	uint32_t getWidth() { return this->width; }
	uint32_t getHeight() { return this->height; }
	bool hasAlphaChannel() { return bitsPerPixel == 32; }

	char* getPixelsData() {	return reinterpret_cast<char*>(pixels.data()); }

};

#endif
