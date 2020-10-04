#include "./headers/image/image.h"

namespace Image {
	ImageStruct getImageData(const char* fileName) {
		int width, height, nChannels;
		unsigned char *imgData = stbi_load(fileName, &width, &height, &nChannels, 0);
		if (imgData == NULL) {
			std::string errMsg = "Error loading image: " + std::string(fileName);
			Logger::logError("Image", errMsg);
		} else {
			std::string infoMsg = "Loaded file: '" + std::string(fileName) + "'; ";
			infoMsg +=  "Dimensions: (" + std::to_string(width) + ", " + std::to_string(height) + "); ";
			infoMsg +=  "Channels: " + std::to_string(nChannels);
			Logger::logInfo("Image", infoMsg);
		}

		// Creating Image object to return
		ImageStruct imageObj;	
		imageObj.width = width;
		imageObj.height = height;
		imageObj.nChannels = nChannels;
		imageObj.imgData = imgData;

		return imageObj;
	}

	int writeImageToFile(const char* fileToWrite, ImageStruct imageObj) {
		// Writing to image file ;;; "./data/tmp2.png"
		int writeSuccessful = stbi_write_png(
			fileToWrite, 
			imageObj.width, imageObj.height, imageObj.nChannels, 
			imageObj.imgData, 
			imageObj.width * imageObj.nChannels);
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
		bool channelIsValid = targetChannel < imageObj.nChannels;
		if (channelIsValid) {
			unsigned bytePerPixel = imageObj.nChannels;
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
		unsigned bytePerPixel = imageObj.nChannels;
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
		unsigned bytePerPixel = imageObj.nChannels;
		this->width = imageObj.width;
		this->height = imageObj.height;
		this->nChannels = imageObj.nChannels;

		Pixel px = createPixel(imageObj.nChannels);
		Matrix::Matrix<Pixel>* pixelList = new Matrix::Matrix<Pixel>(this->height, this->width, px);
		this->pixels = pixelList;
		for (unsigned int rowIdx = 0; rowIdx < imageObj.height; ++rowIdx) {
			for (int colIdx = 0; colIdx < imageObj.width; ++colIdx) {
				unsigned char* pixelOffset = imageObj.imgData + (colIdx + imageObj.height*rowIdx) * bytePerPixel;
				Pixel px = createPixel(pixelOffset, imageObj.nChannels);
				this->pixels->data[colIdx + imageObj.height*rowIdx] = px;
			}
		}
	}

	ImageAsPixels::ImageAsPixels(void) {
		this->width = 0;
		this->height = 0;
		this->nChannels = 0;
		this->pixels->clear();
	}

	ImageAsPixels::ImageAsPixels(const ImageStruct& imageObj) {
		this->_initWithImageStruct(imageObj);
	}

	ImageAsPixels::ImageAsPixels(const char* fileName) {
		ImageStruct imageObj = getImageData(fileName);
		this->_initWithImageStruct(imageObj);
	}

	Matrix::Matrix<Pixel>* ImageAsPixels::getPixels() {	// returns this->pixels
		return this->pixels;
	}

	ImageStruct& ImageAsPixels::getImageStructPropertiesOnly() {
		ImageStruct imgSt;
		imgSt.height = this->height;
		imgSt.width = this->width;
		imgSt.nChannels = this->nChannels;
		imgSt.imgData = nullptr;
		ImageStruct& imgStRef = imgSt;
		return imgStRef;
	}

	void ImageAsPixels::info(void) {
		for (auto px : this->pixels->data) {
			dumpPixelInfo(px);
		}
	}

	void ImageAsPixels::info(const unsigned int& targetChannel, const int& cellWidth) {
		bool channelIsValid = this->nChannels > targetChannel;
		if (channelIsValid) {
			unsigned long int pixelCount = 0;
			for (auto px : this->pixels->data) {
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
