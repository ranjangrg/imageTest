#pragma once	// include only once

#ifndef __IMAGE_H
#define __IMAGE_H

#include "../basic.h"
#include "./stb.h"
#include "./pixel.h"
#include "../matrix.hpp"

#include <cinttypes>	// for 32 bit integers

//#pragma pack(2)	// to disable auto-padding of bytes in structs

namespace Image {
	// a struct that holds image data including number of channels and actual pixel data per channel
	typedef struct image {
		int width, height, nChannels;
		unsigned char *imgData;
		//char header[2] {'B', 'M'};	// C++11 allows assignment like this
	} ImageStruct;
}

namespace Image {
	// some useful methods related to image e.g. read/write imagefiles
	ImageStruct getImageData(const char* fileName);
	int writeImageToFile(const char* fileToWrite, ImageStruct imageObj);
	void printPixels(const ImageStruct& imageObj, const unsigned int targetChannel);
	void modifyPixels(ImageStruct &imageObj, const char colour);
	void clearImageData(ImageStruct imageObj);
	// TODO convolute method
	//ImageStruct& convoluteImageUsingKernel (const ImageStruct& imageSt, const kernel);
}

namespace Image {
	// 	=============================
	// 	 ImageAsPixels class methods
	//	=============================
	class ImageAsPixels {
		private:
			int width, height, nChannels;
			Matrix::Matrix<Pixel>* pixels;	// storing pixels through a MATRIX pointer
			// internal methods
			void _initWithImageStruct(const ImageStruct& imageObj); // used by some constructors
		public:
			ImageAsPixels(void);
			ImageAsPixels(const ImageStruct& imageObj);	// use an imageStruct (struct/obj?) as constructor param
			ImageAsPixels(const char* fileName);

			// displays all pixel data i.e. calls dumpPixelInfo() with each pixel
			void info(void);

			// e.g. if channels are rgb, 
			// targetChannel = 0, info(0) gives RED, 
			// targetChannel = 1, info(1) gives GREEN, 
			// targetChannel = 2, info(2) gives BLUE, 
			void info(const unsigned int& targetChannel, const int& cellWidth = 3);
	};
}

#endif