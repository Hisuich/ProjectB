#include "BMP.h"

BMP::BMP(std::string filePath)
{
	fstream image(filePath, ios::in | ios::binary);
	if (!image.is_open()) { throw invalid_argument("Error: File is not opened"); }

	fileName = filePath;
	image.seekg(0, ios::end);
	size_t length = image.tellg();
	image.seekg(0, ios::beg);

	vector<uint8_t> fileInfo(54);
	image.read(reinterpret_cast<char*>(fileInfo.data()), 54);

	bitsPerPixel = fileInfo[28] + (fileInfo[29] << 8);
	width = fileInfo[18] + (fileInfo[19] << 8);
	height = fileInfo[22] + (fileInfo[23] << 8);
	cout << "name: " << filePath.c_str();
	cout << " width " << width << " " << "height " << height << endl;
	uint32_t pixelOffset = fileInfo[10] + (fileInfo[11] << 8);
	uint32_t size = width * 4 * height;
	pixels.resize(size);

	image.seekg(pixelOffset, ios::beg);
	image.read(reinterpret_cast<char*>(pixels.data()), size);
	image.close();
}



