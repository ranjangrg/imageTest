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

	Pixel addPixels(const Pixel& lhs, const Pixel& rhs);
	Pixel subtractPixels(const Pixel& lhs, const Pixel& rhs);
}

// TODO: implement operator methods for pixel objects
// operator methods for pixel objects
namespace Image {
	// mathematical operators
	Pixel& operator + (const Pixel& lhs, const Pixel& rhs);
	Pixel& operator - (const Pixel& lhs, const Pixel& rhs);

	// IO operators
	std::ostream& operator << (std::ostream& os, const Pixel& px);
}

#endif