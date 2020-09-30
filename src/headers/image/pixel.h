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
	/*
	class Pixel {
	public:
		unsigned char* channels;
		unsigned int nChannels;

		Pixel(const unsigned int& defaultValue = 0);
		Pixel(std::initializer_list<unsigned char> pixelValues);
		Pixel(unsigned char* pixelOffset, unsigned int nChannels);	// args: data, number of channels e.g. rgb has 3 channels

		// better to have external method handle this instead of 
		// making this a class method (it may increase memory footprint)
		// of each pixel
		//const void info(void); 
	};
	*/
}

namespace Image {
	Pixel createPixel(const unsigned int& defaultValue = 0);
	Pixel createPixel(std::initializer_list<unsigned char> pixelValues);
	Pixel createPixel(unsigned char* pixelOffset, unsigned int nChannels);
}

#endif