#ifndef __BMP_H
#define __BMP_H

#include "./basic.h"
#include "./stb.h"

#include <cinttypes>	// for 32 bit integers
#include <iomanip>

//#pragma pack(2)	// to disable auto-padding of bytes in structs

namespace Image {
	typedef struct image {
		int width, height, channels;
		unsigned char *imgData;
		//char header[2] {'B', 'M'};	// C++11 allows assignment like this
	} Image;

	Image getImageData(const char* fileName);
	int writeImageToFile(const char* fileToWrite, Image imageObj);
	void printPixels(Image imageObj, const char colour);
	void clearImageData(Image imageObj);
}

#endif