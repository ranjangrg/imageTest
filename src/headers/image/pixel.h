#ifndef __PIXEL_H
#define __PIXEL_H

#include "../basic.h"

namespace Image {
	class Pixel {
	public:
		unsigned char* channels;
		unsigned int nChannels;

		Pixel(const unsigned int& defaultValue = 0);
		Pixel(std::initializer_list<unsigned char> pixelValues);
		Pixel(unsigned char* pixelOffset, unsigned int nChannels);	// args: data, number of channels e.g. rgb has 3 channels

		const void info(void);
	};
}

#endif