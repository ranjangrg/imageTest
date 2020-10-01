#include "./headers/image/image.h"

namespace Image {
	ImageStruct getImageData(const char* fileName) {
		int width, height, channels;
		unsigned char *imgData = stbi_load(fileName, &width, &height, &channels, 0);
		if (imgData == NULL) {
			std::string errMsg = "Error loading image: " + std::string(fileName);
			Logger::logError("Image", errMsg);
		} else {
			std::string infoMsg = "Loaded file: '" + std::string(fileName) + "'; ";
			infoMsg +=  "Dimensions: (" + std::to_string(width) + ", " + std::to_string(height) + "); ";
			infoMsg +=  "Channels: " + std::to_string(channels);
			Logger::logInfo("Image", infoMsg);
		}

		// Creating Image object to return
		ImageStruct imageObj;	
		imageObj.width = width;
		imageObj.height = height;
		imageObj.channels = channels;
		imageObj.imgData = imgData;

		return imageObj;
	}

	int writeImageToFile(const char* fileToWrite, ImageStruct imageObj) {
		// Writing to image file ;;; "./data/tmp2.png"
		int writeSuccessful = stbi_write_png(
			fileToWrite, 
			imageObj.width, imageObj.height, imageObj.channels, 
			imageObj.imgData, 
			imageObj.width * imageObj.channels);
		if (writeSuccessful == 1) {
			std::string infoMsg = "Write Successful. File: " + std::string(fileToWrite);
			Logger::logInfo("Image", infoMsg);
		} else {
			std::string errMsg = "Write failed! File: " + std::string(fileToWrite);
			Logger::logError("Image", errMsg);
			writeSuccessful = -1;
		} 
		return writeSuccessful;
	}

	void printPixels(const ImageStruct& imageObj, const unsigned int targetChannel) {
		// make sure the channel is valid or else
		// it will dump garbage data
		bool channelIsValid = targetChannel < imageObj.channels;
		if (channelIsValid) {
			unsigned bytePerPixel = imageObj.channels;
			for (int pixelY = 0; pixelY < imageObj.width; ++pixelY) {
				for (int pixelX = 0; pixelX < imageObj.height; ++pixelX) {
					unsigned char* pixelOffset = imageObj.imgData + (pixelX + imageObj.height*pixelY) * bytePerPixel;
					std::cout << std::setw(3) << int(pixelOffset[targetChannel]) << ' ';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		} else {
			std::string errMsg = "Invalid channel requested via: printPixels(targetChannel = " + std::to_string(targetChannel) + ")";
			Logger::logError("Image", errMsg);
		}
	}

	void modifyPixels(ImageStruct &imageObj, const char colour) {
		Logger::logInfo("Image", "Image Modification in progress ... ");
		int rgbIdx = 0;	// for red
		if (colour == 'g') { rgbIdx = 1; } 
		if (colour == 'b') { rgbIdx = 2; }
		unsigned bytePerPixel = imageObj.channels;
		for (int pixelY = 0; pixelY < imageObj.width; ++pixelY) {
			for (int pixelX = 0; pixelX < imageObj.height; ++pixelX) {
				unsigned char* pixelOffset = imageObj.imgData + (pixelX + imageObj.height*pixelY) * bytePerPixel;
				if ( (pixelY + pixelX) > imageObj.width ) {
					unsigned char offset = ( (3 * pixelOffset[rgbIdx] + 5 * pixelOffset[rgbIdx]) ) % 256 ;
					if (pixelOffset[rgbIdx] == 0) {
						pixelOffset[rgbIdx] = (pixelOffset[rgbIdx] - (offset * 2)) % 256;
					} else {
						pixelOffset[rgbIdx] = (pixelOffset[rgbIdx] + (offset * 2)) % 256;
					}
				}
			}
		}
	}

	void clearImageData(ImageStruct imageObj) {
		Logger::logInfo("Image", "ImageStruct freed!");
		stbi_image_free(imageObj.imgData);
	}
}

namespace Image {
	// 	=============================
	// 	 ImageAsPixels class methods
	//	=============================

	void ImageAsPixels::_initWithImageStruct(const ImageStruct& imageObj) {
		unsigned bytePerPixel = imageObj.channels;
		this->width = imageObj.width;
		this->height = imageObj.height;
		this->channels = imageObj.channels;
		for (int pixelY = 0; pixelY < imageObj.width; ++pixelY) {
			for (int pixelX = 0; pixelX < imageObj.height; ++pixelX) {
				unsigned char* pixelOffset = imageObj.imgData + (pixelX + imageObj.height*pixelY) * bytePerPixel;
				Pixel px = createPixel(pixelOffset, imageObj.channels);
				this->pixels.push_back(px);
			}
		}
	}

	ImageAsPixels::ImageAsPixels(void) {
		this->width = 0;
		this->height = 0;
		this->channels = 0;
		this->pixels.clear();
	}

	ImageAsPixels::ImageAsPixels(const ImageStruct& imageObj) {
		this->_initWithImageStruct(imageObj);
	}

	ImageAsPixels::ImageAsPixels(const char* fileName) {
		ImageStruct imageObj = getImageData(fileName);
		this->_initWithImageStruct(imageObj);
	}

	void ImageAsPixels::info(void) {
		for (auto px : this->pixels) {
			dumpPixelInfo(px);
		}
	}

	void ImageAsPixels::info(const unsigned int& targetChannel, const int& cellWidth) {
		bool channelIsValid = this->channels > targetChannel;
		if (channelIsValid) {
			unsigned long int pixelCount = 0;
			for (auto px : this->pixels) {
				// cellWidth ONLY for string format
				std::cout << std::setw(cellWidth) << (int)(px.channels[targetChannel]) << ' ';
				if ( ( (++pixelCount) % this->width) == 0 ) {
					std::cout << std::endl;
				}
			}
		} else {
			std::string errMsg = "Invalid channel requested via: info(targetChannel = " + std::to_string(targetChannel) + ")";
			Logger::logError("Image", errMsg);
		}
	}

}
