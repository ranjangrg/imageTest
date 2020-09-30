#include "./headers/image/pixel.h"

//namespace Image {
	/*
	Pixel::Pixel(const unsigned int& defaultValue) {
		this->nChannels = 1;
		this->channels = new unsigned char[this->nChannels];
		this->channels[0] = defaultValue;
	}

	Pixel::Pixel(std::initializer_list<unsigned char> pixelValues) {
		this->nChannels = pixelValues.size();
		this->channels = new unsigned char[this->nChannels]; // maybe call constructor(int) somehow
		std::copy(pixelValues.begin(), pixelValues.end(), this->channels);
	}

	Pixel::Pixel(unsigned char* pixelOffset, unsigned int nChannels) {
		this->channels = pixelOffset;
		this->nChannels = nChannels;
	}
	*/

	/*
	// see "pixel.h" for details on excluding this method
	const void Pixel::info(void) {
		std::cout << "[INFO] [PIXEL] Channels: " << this->nChannels << "; Values: ";
		for (unsigned int idx = 0; idx < this->nChannels; ++idx) {
			std::cout << (int)(this->channels[idx]) << ", ";
		}
		std::cout <<std::endl;
	}
	*/
//}

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
}
