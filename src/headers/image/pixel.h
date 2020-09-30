#ifndef __PIXEL_H
#define __PIXEL_H

#include "../basic.h"

namespace Image {
	// implementing pixel as struct instead of a class
	// reason: possible performance and less memory (no proof!)
	typedef struct pixel {
		unsigned char* channels;
		unsigned int nChannels;
	} Pixel;
}

namespace Image {
	Pixel createPixel(const unsigned int& defaultValue = 0);
	Pixel createPixel(std::initializer_list<unsigned char> pixelValues);
	Pixel createPixel(unsigned char* pixelOffset, unsigned int nChannels);

	void dumpPixelInfo(const Pixel& pixel);
}

#endif