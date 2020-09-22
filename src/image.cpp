#include "./headers/image.h"

namespace Image {
	Image getImageData(const char* fileName) {
		int width, height, channels;
		unsigned char *imgData = stbi_load(fileName, &width, &height, &channels, 0);
		if (imgData == NULL) {
			std::cout << "Error loading image." << std::endl;		
		} else {
			std::cout << "Loaded image: " << width << ", " << height << ", " << channels << std::endl;
		}

		// Creating Image object to return
		Image imageObj;	
		imageObj.width = width;
		imageObj.height = height;
		imageObj.channels = channels;
		imageObj.imgData = imgData;

		return imageObj;
	}

	int writeImageToFile(const char* fileToWrite, Image imageObj) {
		// Writing to image file ;;; "./data/tmp2.png"
		return stbi_write_png(fileToWrite, imageObj.width, imageObj.height, imageObj.channels, imageObj.imgData, imageObj.width * imageObj.channels);
	}

	void printPixels(Image imageObj, const char colour) {
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

	void clearImageData(Image imageObj) {
		stbi_image_free(imageObj.imgData);
	}
}