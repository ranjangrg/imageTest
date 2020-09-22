#include "./headers/main.h"

int main() {
	Image::Image testImage;

	testImage = Image::getImageData("./data/pixel.png");
	Image::printPixels(testImage, 'r');
	Image::printPixels(testImage, 'g');
	Image::printPixels(testImage, 'b');

	Image::writeImageToFile("./data/delme.png", testImage);

	return 0;
}
