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
		std::string infoMsg = "Channels: " + std::to_string(pixel.nChannels) + "; Values: ";
		for (unsigned int idx = 0; idx < pixel.nChannels; ++idx) {
			infoMsg += std::to_string((int)(pixel.channels[idx])) + ", ";
		}
		Logger::logInfo("Pixel", infoMsg);
	}

	Pixel addPixels(const Pixel& lhs, const Pixel& rhs) {
		unsigned int nChannelsLhs = lhs.nChannels;
		unsigned int nChannelsRhs = rhs.nChannels;
		if (nChannelsLhs != nChannelsRhs) {
			throw pixelChannelCountNotSameException();
		}
		Pixel sumPx;
		sumPx.nChannels = nChannelsLhs;
		sumPx.channels = new unsigned char[sumPx.nChannels];
		for (unsigned int channelIdx = 0; channelIdx < sumPx.nChannels; ++channelIdx) {
			unsigned short sum = lhs.channels[channelIdx] + rhs.channels[channelIdx];
			sumPx.channels[channelIdx] = sum % int(std::numeric_limits<u_char>::max());
		}
		return sumPx;
	}

	// lot of repeated codes as in addPixels(); due to unsigned overflow with subtraction
	Pixel subtractPixels(const Pixel& lhs, const Pixel& rhs) {
		unsigned int nChannelsLhs = lhs.nChannels;
		unsigned int nChannelsRhs = rhs.nChannels;
		if (nChannelsLhs != nChannelsRhs) {
			throw pixelChannelCountNotSameException();
		}
		Pixel diffPx;
		diffPx.nChannels = nChannelsLhs;
		diffPx.channels = new unsigned char[diffPx.nChannels];
		for (unsigned int channelIdx = 0; channelIdx < diffPx.nChannels; ++channelIdx) {
			// check for overflow between unsigned char/ints
			if (rhs.channels[channelIdx] >= lhs.channels[channelIdx]) {
				diffPx.channels[channelIdx] = 0;
			} else {
				diffPx.channels[channelIdx] = lhs.channels[channelIdx] - rhs.channels[channelIdx];
			}
		}
		return diffPx;
	}
}

namespace Image {
	// mathematical operations
	Pixel& operator + (const Pixel& lhs, const Pixel& rhs) {
		Pixel sumPx = addPixels(lhs, rhs);
		Pixel& sumPxRef = sumPx;
		return sumPxRef;
	}

	Pixel& operator - (const Pixel& lhs, const Pixel& rhs) {
		Pixel diffPx = subtractPixels(lhs, rhs);
		Pixel& diffPxRef = diffPx;
		return diffPxRef;
	}

	std::ostream& operator << (std::ostream& os, const Pixel& px) {
		if (px.nChannels > 0) {
			os << '(' << std::to_string((int)(px.channels[0]));
			if (px.nChannels > 1) {
				for (unsigned int idx = 1; idx < px.nChannels; ++idx) {
					os << ',' << std::to_string((int)(px.channels[idx]));
				}
			}
			os << ')';
		}
		return os;
	}
}