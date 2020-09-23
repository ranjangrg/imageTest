#include "./headers/main.h"

int imageTest() {
	Image::Image testImage;

	testImage = Image::getImageData("./data/pixel.png");
	Image::printPixels(testImage, 'r');
	Image::printPixels(testImage, 'g');
	Image::printPixels(testImage, 'b');

	Image::modifyPixels(testImage, 'r');
	Image::modifyPixels(testImage, 'b');

	Image::writeImageToFile("./data/delme.png", testImage);

	Image::printPixels(testImage, 'r');
	Image::printPixels(testImage, 'g');
	Image::printPixels(testImage, 'b');

	Image::clearImageData(testImage);

	return 0;
}

int main() {
	imageTest();
	
	return 0;
}
