#pragma once	// include only once

#ifndef __IMAGE_H
#define __IMAGE_H

#include "../basic.h"
#include "./stb.h"
#include "./pixel.h"

#include <cinttypes>	// for 32 bit integers

//#pragma pack(2)	// to disable auto-padding of bytes in structs

namespace Image {
	typedef struct image {
		int width, height, channels;
		unsigned char *imgData;
		//char header[2] {'B', 'M'};	// C++11 allows assignment like this
	} ImageStruct;

	ImageStruct getImageData(const char* fileName);
	int writeImageToFile(const char* fileToWrite, ImageStruct imageObj);
	void printPixels(const ImageStruct& imageObj, const char colour);
	void modifyPixels(ImageStruct &imageObj, const char colour);
	void clearImageData(ImageStruct imageObj);
}

namespace Image {
	// 	=============================
	// 	 ImageAsPixels class methods
	//	=============================
	class ImageAsPixels {
	private:
		int width, height, channels;
		std::vector<std::vector<Pixel>> pixels;
	public:
		ImageAsPixels(void);
		ImageAsPixels(const ImageStruct& imageObj);

		// displays all pixel data i.e. calls pixel.info() for each pixel
		void info();

		// e.g. if channels are rgb, 
		// targetChannel = 0, info(0) gives RED, 
		// targetChannel = 1, info(1) gives GREEN, 
		// targetChannel = 2, info(2) gives BLUE, 
		void info(const int& targetChannel, const int& cellWidth = 3);
	};
}

#endif