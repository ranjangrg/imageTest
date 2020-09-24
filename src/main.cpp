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
	Matrix<int> mA = Matrix<int>(3, 3); 
	mA.edit(0,0, 5);
	mA.edit(0,2, 7);
	mA.edit(2,1, 3);

	Matrix<int> mB = Matrix<int>(3, 3); 
	mB.edit(0,9, 2);
	mB.edit(0,2, -2);
	mB.edit(2,1, 2);

	Matrix<int> mC = Matrix<int>(5, 5); 

	//std::cout << "Elem: " << mB(0,2) << std::endl;

	Matrix<int> mSumPass1 = mA + mB;
	Matrix<int> mSumPass2 = mB + mA;
	Matrix<int> mSumFail1 = mA + mC;
	Matrix<int> mSumFail2 = mB + mC;

	Matrix<int> mDiffPass1 = mA - mB;
	Matrix<int> mDiffPass2 = mB - mA;
	Matrix<int> mDiffFail1 = mA - mC;
	Matrix<int> mDiffFail2 = mB - mC;
	Matrix<int> mDiffFail3 = mC - mA;
	Matrix<int> mDiffFail4 = mC - mB;

	std::cout << "mA:" << std::endl;
	mA.info(); 
	std::cout << "mB:" << std::endl;
	mB.info();
	std::cout << "mC:" << std::endl;
	mC.info();

	/*
	std::cout << " = " << std::endl;
	mSum.info();
	std::cout << " (-) = " << std::endl;
	mDiff.info();
	*/

	return 0;
}

int main() {
	matrixTest();
	
	return 0;
}
