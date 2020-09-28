#include "./headers/main.h"

int imageTest() {
	Image::ImageStruct testImage;

	testImage = Image::getImageData("./data/pixel.png");
	Image::printPixels(testImage, 'r');
	Image::printPixels(testImage, 'g');
	Image::printPixels(testImage, 'b');

	Image::modifyPixels(testImage, 'r');
	Image::modifyPixels(testImage, 'g');
	Image::modifyPixels(testImage, 'b');

	Image::writeImageToFile("./data/delme.png", testImage);

	Image::printPixels(testImage, 'r');
	Image::printPixels(testImage, 'g');
	Image::printPixels(testImage, 'b');

	Image::clearImageData(testImage);

	return 0;
}

int matrixTest() {

	// Matrix initialization
	Matrix::Matrix<int> mA = Matrix::Matrix<int>(3, 3); 
	mA.edit(0, 0, 5);
	mA.edit(0, 2, 7);
	mA.edit(2, 1, 3);
	std::vector<int> row {1, 2, 3};
	mA.addRow(row);
	mA.addRow({5, 6, 7, 9});

	Matrix::Matrix<int> mB = Matrix::Matrix<int>(3, 3); 
	mB.edit(0, 9, 2);
	mB.edit(0, 2, -2);
	mB.edit(2, 1, 2);

	Matrix::Matrix<int> mC = Matrix::Matrix<int>(5, 5); 

	//std::cout << "Elem: " << mB(0,2) << std::endl;

	Matrix::Matrix<int> mSumPass1 = mA + mB;
	Matrix::Matrix<int> mSumPass2 = mB + mA;
	Matrix::Matrix<int> mSumFail1 = mA + mC;
	Matrix::Matrix<int> mSumFail2 = mB + mC;

	Matrix::Matrix<int> mDiffPass1 = mA - mB;
	Matrix::Matrix<int> mDiffPass2 = mB - mA;
	Matrix::Matrix<int> mDiffFail1 = mA - mC;
	Matrix::Matrix<int> mDiffFail2 = mB - mC;
	Matrix::Matrix<int> mDiffFail3 = mC - mA;
	Matrix::Matrix<int> mDiffFail4 = mC - mB;

	Matrix::Matrix<int> mD({
		{1, 2},
		{3, 4},
		{1, 4}
		});
	
	Matrix::Matrix<int> mE({1, 2});

	// Matrix dump
	std::cout << "mA:" << std::endl;
	mA.info(); 
	std::cout << "mB:" << std::endl;
	mB.info();
	std::cout << "mC:" << std::endl;
	mC.info();
	std::cout << "mD:" << std::endl;
	mD.info();
	std::cout << "mE:" << std::endl;
	mE.info();

	return 0;
}

int pixelTest() {
	Image::Pixel dot( {20,40,0,4} );
	dot.info();

	return 0;
}

int imageAsPixelsTest() {
	Image::ImageStruct testImage;
	testImage = Image::getImageData("./data/pixel.png");

	Image::ImageAsPixels imgPx1(testImage);
	Image::ImageAsPixels imgPx2;
	Image::ImageAsPixels imgPx3("./data/pixel.png");

	/*
	imgPx1.info();
	std::cout << "RED:" <<  std::endl;
	imgPx1.info(0);
	std::cout << "GREEN:" <<  std::endl;
	imgPx1.info(1);
	std::cout << "BLUE:" <<  std::endl;
	imgPx1.info(2);

	imgPx2.info(0);
	*/

	//imgPx3.info();
	std::cout << "RED:" <<  std::endl;
	imgPx3.info(0);
	std::cout << "GREEN:" <<  std::endl;
	imgPx3.info(1);
	std::cout << "BLUE:" <<  std::endl;
	imgPx3.info(2);

	return 0;
}

int main() {
	//imageTest();
	//pixelTest();
	//imageAsPixelsTest();
	matrixTest();
	
	return 0;
}
