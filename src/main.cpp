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

int matrixTest() {
	Matrix<int> m = Matrix<int>(10, 10); 
	m.edit(3,4, 100);

	m.info();

	return 0;
}

int main() {
	matrixTest();
	
	return 0;
}
