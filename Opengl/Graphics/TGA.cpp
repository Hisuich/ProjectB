#include "TGA.h"

TGA::TGA(const char * filename)
{
	char imageType;
	std::vector<uint8_t> size(4);
	char* badInfo = new char(13);

	std::fstream image(filename, std::ios::binary | std::ios::in);
	if (!image.is_open())
	{
		throw "File is not open";
	}

	image.read(badInfo, 2);
	image.read(&imageType, 1);
	/*if (imageType != 2 && imageType != 3)
	{
		image.close();
		throw "we don't need this";
	}*/

	image.read(badInfo, 9);
	image.read(reinterpret_cast<char*>(size.data()) , 4);
	width = size[0] + (size[1] << 8);
	height = size[2] + (size[3] << 8);
		
	image.read(&bpp, 1);
	image.read(badInfo, 1);
	int imageSize = width * height * bpp;
	pixels.resize(imageSize);
	image.read(reinterpret_cast<char*>(pixels.data()), imageSize);
	image.close();
}
