#include "./headers/main.h"

#include <iomanip>

int main() {
	//Image::bitmapHeader testImage;

	int width, height, channels;
	unsigned char *imgData = stbi_load("./data/pixel.png", &width, &height, &channels, 0);
	if (imgData == NULL) {
		std::cout << "Error loading image." << std::endl;		
	} else {
		std::cout << "Loaded image: " << width << ", " << height << ", " << channels << std::endl;
		/* */
		for (int x = 0; x < (width * height); ++x) {
			std::cout << std::setw(3) << int(imgData[x]) << ' ';
			if ( ((x+1) % width) == 0 ) {
				std::cout << std::endl;
			}
		}
		std::cout << std::endl;
		/* RED */
		unsigned bytePerPixel = channels;
		for (int pixelY = 0; pixelY < width; ++pixelY) {
			for (int pixelX = 0; pixelX < height; ++pixelX) {
				unsigned char* pixelOffset = imgData + (pixelX + height*pixelY) * bytePerPixel;
				std::cout << std::setw(3) << int(pixelOffset[0]) << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		/* GREEN */
		for (int pixelY = 0; pixelY < width; ++pixelY) {
			for (int pixelX = 0; pixelX < height; ++pixelX) {
				unsigned char* pixelOffset = imgData + (pixelX + height*pixelY) * bytePerPixel;
				std::cout << std::setw(3) << int(pixelOffset[1]) << ' ';
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		/* BLUE */
		for (int pixelY = 0; pixelY < width; ++pixelY) {
			for (int pixelX = 0; pixelX < height; ++pixelX) {
				unsigned char* pixelOffset = imgData + (pixelX + height*pixelY) * bytePerPixel;
				std::cout << std::setw(3) << int(pixelOffset[2]) << ' ';
				pixelOffset[2] = (pixelOffset[2] - 2) % 255;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	// Writing to image file 
	stbi_write_png("./data/tmp2.png", width, height, channels, imgData, width * channels);
	
	stbi_image_free(imgData);

	return 0;
}