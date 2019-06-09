#pragma once

#include <iostream>
#include <vector>
#include <fstream>

class TGA
{
private:
	uint32_t width, height;
	char bpp;
	std::vector<uint8_t> pixels;

public:
	TGA(const char* filename);
	std::vector<uint8_t> getPixels() { return this->pixels; }
	uint32_t getWidth() { return this->width; }
	uint32_t getHeight() { return this->height; }
	bool hasAlphaChannel() { return bpp == 32; }

	char* getPixelsData() { return reinterpret_cast<char*>(pixels.data()); }
};