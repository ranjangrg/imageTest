#include "./headers/main.h"

void testStart(std::string testName) { 
	std::string msg = std::string(testName) + "' STARTED."; 
	Logger::logInfo("TEST", msg);
}
void testEnd(std::string testName) { 
	std::string msg = std::string(testName) + "' ENDED."; 
	Logger::logInfo("TEST", msg);
}

int imageTest() {
	std::string testName = "imageTest()";
	testStart(testName);

	bool showDumpBefore = false;
	bool modifyImage = true;
	bool showDumpAfter = false;
	Image::ImageStruct testImage;

	testImage = Image::getImageData("./data/pixel.png");
	//testImage = Image::getImageData("./data/test.jpg");
	
	Image::printPixels(testImage, 50);

	if (showDumpBefore) {
		// Image data dump (before modification)
		Image::printPixels(testImage, 0);
		Image::printPixels(testImage, 1);
		Image::printPixels(testImage, 2);
	}

	if (modifyImage) {
		// image modification
		Image::modifyPixels(testImage, 'r');
		Image::modifyPixels(testImage, 'g');
		Image::modifyPixels(testImage, 'b');
	}

	Image::writeImageToFile("./data/delme.png", testImage);

	if (showDumpAfter) {
		// Image data dump (after modification)
		Image::printPixels(testImage, 0);
		Image::printPixels(testImage, 1);
		Image::printPixels(testImage, 2);
	}

	Image::clearImageData(testImage);

	testEnd(testName);
	return 0;
}

int matrixTest() {
	std::string testName = "matrixTest()";
	testStart(testName);
	// Matrix initialization
	Matrix::Matrix<int> mA(5, 5);
	Matrix::Matrix<int> mB({
		{1, 2, 9},
		{3, 4, 1},
		{1, 4, 6},
		{10, 54, -9}
		});
	Matrix::Matrix<int> mC( {1, 2, 9} );
	mC.addRow({2, 8, 1});
	mC.edit(0, 0, 500);

	Matrix::Matrix<float> mD( {{0.5, 3.14, 5.6, -2.8}} );
	
	Matrix::Matrix<int> mScalar1 = mC * 10;
	Matrix::Matrix<float> mScalar2 = mC * float(1.25);
	Matrix::Matrix<double> mScalar3 = mC * double(-1.055);

	Matrix::Matrix<int> mSum = mC;
	Matrix::Matrix<int> mDiff = mScalar1 - mSum;

	// Matrix dump
	std::cout << "mA:" << std::endl;
	mA.info();
	std::cout << "mB:" << std::endl;
	mB.info();
	std::cout << "mC:" << std::endl;
	mC.info();
	std::cout << "mD:" << std::endl;
	mD.info();
	std::cout << "mScalar1:" << std::endl;
	mScalar1.info();
	std::cout << "mScalar2:" << std::endl;
	mScalar2.info();
	std::cout << "mScalar3:" << std::endl;
	mScalar3.info();
	std::cout << "mSum:" << std::endl;
	mSum.info();
	std::cout << "mDiff:" << std::endl;
	mDiff.info();

	// these methods should fail and throw exception
	std::cout << "mDiff: get(1000, 0) ";
	try {
		std::cout << mDiff(1000,0) << std::endl;
	} catch (Matrix::getException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "mDiff: addRow({1,4,3,2,5,6}) ";
	try {
		mDiff.addRow({1,4,3,2,5,6});
	} catch (Matrix::addRowException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "mDiff: mDiff.edit(1000,0, -8)";
	try {
		mDiff.edit(1000,0, -8);
	} catch (Matrix::editException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "mBadArgument({ ... })";
	try {
		Matrix::Matrix<int> mBadArgument({
			{1, 2, 9},
			{3, 4, 1},
			{1, 4, 6},
			{10, 54, -9, 0}
			});
	} catch (Matrix::constructorBadArgumentException& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "mC + mD:";
	try {
		Matrix::Matrix<float> mSumBad = Matrix::_addMatrices(mD, mC);
	} catch (Matrix::addException& e) {
		std::cout << e.what() << std::endl;
	}

	testEnd(testName);
	return 0;
}

int pixelTest() {
	std::string testName = "pixelTest()";
	testStart(testName);

	Image::Pixel dot = Image::createPixel( {20,40,0,4} );
	Image::dumpPixelInfo(dot);
	
	testEnd(testName);
	return 0;
}

int imageAsPixelsTest() {
	std::string testName = "imageAsPixelsTest()";
	testStart(testName);

	Image::ImageStruct testImage;
	testImage = Image::getImageData("./data/pixel.png");
	//testImage = Image::getImageData("./data/test.jpg");

	Image::ImageAsPixels imgPx1(testImage);
	Image::ImageAsPixels imgPx2;
	Image::ImageAsPixels imgPx3("./data/pixel.png");

	std::cout << "RED:" <<  std::endl;
	imgPx3.info(0);
	std::cout << "GREEN:" <<  std::endl;
	imgPx3.info(1);
	std::cout << "BLUE:" <<  std::endl;
	imgPx3.info(2);

	//imgPx3.info();

	// these methods should fail
	std::cout << "imgPx3.info(200):" <<  std::endl;
	imgPx3.info(200);

	testEnd(testName);
	return 0;
}

int loggerTest() {
	std::string testName = "loggerTest()";
	testStart(testName);

	Logger::logInfo("Pop", "Eaten");
	
	testEnd(testName);
	return 0;
}

int main() {
	std::unordered_map<std::string, bool> performTests = {
		{"imageTest", false},
		{"pixelTest", true},
		{"imageAsPixelsTest", false},
		{"matrixTest", false},
		{"loggerTest", false}
	};

	if (performTests["imageTest"]) {imageTest();}
	if (performTests["pixelTest"]) {pixelTest();}
	if (performTests["imageAsPixelsTest"]) {imageAsPixelsTest();}
	if (performTests["matrixTest"]) {matrixTest();}
	if (performTests["loggerTest"]) {loggerTest();}
	
	return 0;
}
