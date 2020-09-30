#include "./headers/image/pixel.h"

namespace Image {
	Pixel createPixel(const unsigned int& defaultValue) {
		Pixel newPixel;
		newPixel.nChannels = 1;
		newPixel.channels = new unsigned char[newPixel.nChannels];
		newPixel.channels[0] = defaultValue;
		return newPixel;
	}

	Pixel createPixel(std::initializer_list<unsigned char> pixelValues) {
		Pixel newPixel;
		newPixel.nChannels = pixelValues.size();
		newPixel.channels = new unsigned char[newPixel.nChannels]; // maybe call constructor(int) somehow
		std::copy(pixelValues.begin(), pixelValues.end(), newPixel.channels);
		return newPixel;
	}

	Pixel createPixel(unsigned char* pixelOffset, unsigned int nChannels) {
		Pixel newPixel;
		newPixel.channels = pixelOffset;
		newPixel.nChannels = nChannels;
		return newPixel;
	}

	void dumpPixelInfo(const Pixel& pixel) {
		std::cout << "[INFO] [PIXEL] Channels: " << pixel.nChannels << "; Values: ";
		for (unsigned int idx = 0; idx < pixel.nChannels; ++idx) {
			std::cout << (int)(pixel.channels[idx]) << ", ";
		}
		std::cout <<std::endl;
	}
}
