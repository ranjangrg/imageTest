#include "./headers/image/image.h"

namespace Image {
	ImageStruct getImageData(const char* fileName) {
		int width, height, channels;
		unsigned char *imgData = stbi_load(fileName, &width, &height, &channels, 0);
		if (imgData == NULL) {
			std::cout << "Error loading image." << std::endl;		
		} else {
			std::cout << "Loaded image: " << width << ", " << height << ", " << channels << std::endl;
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
		return stbi_write_png(fileToWrite, imageObj.width, imageObj.height, imageObj.channels, imageObj.imgData, imageObj.width * imageObj.channels);
	}

	void printPixels(const ImageStruct& imageObj, const char colour) {
		/* 
		colour: 'r' for RED, 'g' for GREEN and 'b' for BLUE.
		*/
		int rgbIdx = 0;	// for red
		if (colour == 'g') {
			rgbIdx = 1;
		} else if (colour == 'b') {
			rgbIdx = 2;
		}
		/* Printing */
		std::cout << "Colour: " << colour << std::endl;
		unsigned bytePerPixel = imageObj.channels;
		for (int pixelY = 0; pixelY < imageObj.width; ++pixelY) {
			for (int pixelX = 0; pixelX < imageObj.height; ++pixelX) {
				unsigned char* pixelOffset = imageObj.imgData + (pixelX + imageObj.height*pixelY) * bytePerPixel;
				std::cout << std::setw(3) << int(pixelOffset[rgbIdx]) << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void modifyPixels(ImageStruct &imageObj, const char colour) {
		std::cout << "Modification in progress ..." << std::endl;
		int rgbIdx = 0;	// for red
		if (colour == 'g') { rgbIdx = 1; } 
		if (colour == 'b') { rgbIdx = 2; }
		unsigned bytePerPixel = imageObj.channels;
		for (int pixelY = 0; pixelY < imageObj.width; ++pixelY) {
			for (int pixelX = 0; pixelX < imageObj.height; ++pixelX) {
				unsigned char* pixelOffset = imageObj.imgData + (pixelX + imageObj.height*pixelY) * bytePerPixel;
				if (pixelOffset[rgbIdx] == 255) {
					pixelOffset[rgbIdx] = 198 ;
				}
				if (pixelOffset[rgbIdx] == 0) {
					pixelOffset[rgbIdx] = 128 ;
				}
			}
		}
	}

	void clearImageData(ImageStruct imageObj) {
		stbi_image_free(imageObj.imgData);
	}

	// 	=============================
	// 	 ImageAsPixels class methods
	//	=============================

	ImageAsPixels::ImageAsPixels(void) {
		this->width = 0;
		this->height = 0;
		this->channels = 0;
		this->pixels.clear();
	}

	ImageAsPixels::ImageAsPixels(const ImageStruct& imageObj) {
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

	void ImageAsPixels::info() {
		for (auto row : this->pixels) {
			for (auto px : row) {
				px.info();
			}
		}
	}

	void ImageAsPixels::info(const int& targetChannel, const int& cellWidth) {
		// cellWidth ONLY for string format
		for (auto row : this->pixels) {
			for (auto px : row) {
				std::cout << std::setw(cellWidth) << (int)(px.channels[targetChannel]) << ' ';
			}
			std::cout << std::endl;
		}
	}

}