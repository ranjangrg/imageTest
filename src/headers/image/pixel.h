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

	// note: unsigned char and overflow using add or subtract
	// to make sense of overflow(s), add pixel maxes pixel value
	// at 255 (if sum exceeds 255) AND subtract pixel mins pixel value
	// at 0 (if diff is -1)
	// modulus oper is used: %
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