#include "./headers/image/image.h"

namespace Image {
	ImageStruct getImageData(const char* fileName) {
		int width, height, channels;
		unsigned char *imgData = stbi_load(fileName, &width, &height, &channels, 0);
		if (imgData == NULL) {
			std::cout << "[ERR] Error loading image: " << fileName << std::endl;		
		} else {
			std::cout << "[INFO] Loaded image: " << fileName;
			std::cout << "; Dimensions: (" << width << ", " << height;
			std::cout << "); Channels: " << channels << std::endl;
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
			std::cout << "[INFO] Write Successful. File: " << fileToWrite << std::endl;
		} else {
			std::cerr << "[ERR] Write failed! File: " << fileToWrite << std::endl;
			writeSuccessful = -1;
		} 
		return writeSuccessful;
	}

	void dumpPixelInfo(const Pixel& pixel) {
		std::cout << "[INFO] [PIXEL] Channels: " << pixel.nChannels << "; Values: ";
		for (unsigned int idx = 0; idx < pixel.nChannels; ++idx) {
			std::cout << (int)(pixel.channels[idx]) << ", ";
		}
		std::cout <<std::endl;
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
			std::cerr << "[ERR] Invalid channel requested via:" << " printPixels(targetChannel = " << targetChannel << ")" << std::endl;
		}
	}

	void modifyPixels(ImageStruct &imageObj, const char colour) {
		std::cout << "[INFO] Image Modification in progress ... " << std::endl;
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
		std::cout << "[INFO] ImageStruct freed!" << std::endl;
		stbi_image_free(imageObj.imgData);
	}
}

namespace Image {
	// 	=============================
	// 	 ImageAsPixels class methods
	//	=============================

	void ImageAsPixels::_initWithImageStruct(const ImageStruct& imageObj) {
		std::vector<Pixel> row;
		unsigned bytePerPixel = imageObj.channels;
		this->width = imageObj.width;
		this->height = imageObj.height;
		this->channels = imageObj.channels;
		for (int pixelY = 0; pixelY < imageObj.width; ++pixelY) {
			row.clear();			
			for (int pixelX = 0; pixelX < imageObj.height; ++pixelX) {
				unsigned char* pixelOffset = imageObj.imgData + (pixelX + imageObj.height*pixelY) * bytePerPixel;
				Pixel px(pixelOffset, imageObj.channels);
				row.push_back(px);
			}
			this->pixels.push_back(row);
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
		for (auto row : this->pixels) {
			for (auto px : row) {
				dumpPixelInfo(px);
			}
		}
	}

	void ImageAsPixels::info(const unsigned int& targetChannel, const int& cellWidth) {
		bool channelIsValid = this->channels > targetChannel;
		if (channelIsValid) {
			// cellWidth ONLY for string format
			for (auto row : this->pixels) {
				for (auto px : row) {
					std::cout << std::setw(cellWidth) << (int)(px.channels[targetChannel]) << ' ';
				}
				std::cout << std::endl;
			}
		} else {
			std::cerr << "[ERR] Invalid channel requested via:" << " info(" << targetChannel << ")" << std::endl;
		}
	}

}