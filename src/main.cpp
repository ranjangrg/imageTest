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

	//testImage = Image::getImageData("./data/pixel.png");
	testImage = Image::getImageData("./data/test.jpg");
	
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
	Matrix::Matrix<int> mA(5, 5, 0);
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

	Image::Pixel dot1 = Image::createPixel( {250,40,0,4} );
	Image::Pixel dot2 = Image::createPixel( {100,0,50,3} );

	Image::Pixel dotSum1 = dot1 + dot2;
	Image::Pixel dotDiff1 = dot1 - dot2;

	// testing Pixel dump methods and operators
	Image::dumpPixelInfo(dot1);
	Image::dumpPixelInfo(dot2);
	Image::dumpPixelInfo(dotSum1);
	Image::dumpPixelInfo(dotDiff1);
	std::cout << dotSum1 << dotDiff1 << std::endl;
	
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

int matrixConvolutionTest() {
	std::string testName = "matrixConvolutionTest()";
	
	Matrix::Matrix<unsigned int> imageMatrix({
		{5, 5, 0, 5, 5}, 
		{5, 0, 5, 0, 5}, 
		{0, 5, 0, 5, 0}, 
		{5, 0, 5, 0, 5}, 
		{5, 5, 0, 5, 5}
	});
	Matrix::Matrix<unsigned int> convMatrix({
		{0, 1, 0}, 
		{2, 2, 5}, 
		{5, 5, 0}
	});

	// correct convoluted matrix
	Matrix::Matrix<unsigned int> predictedMatrix({
		{60, 45, 60, 60, 45},
 		{15, 65, 35, 65, 40},
 		{55, 35, 65, 35, 40},
 		{35, 90, 35, 65, 60},
 		{40, 20, 40, 35, 25}
	});

	Matrix::Matrix<unsigned int> convolutedImageMatrix = Matrix::_convoluteUsingMatrix(imageMatrix, convMatrix);

	// dumping matrices
	imageMatrix.info();
	convMatrix.info();
	convolutedImageMatrix.info();
	predictedMatrix.info();

	bool convTestSuccessful = convolutedImageMatrix == predictedMatrix;
	std::string testResultMessage = "Convolution test ";
	testResultMessage += (convTestSuccessful) ? "successful." : "failed!";
	Logger::logInfo("TEST", testResultMessage);

	// TESTING convoluting Pixel matrix 
	Image::Pixel dot1 = Image::createPixel( {2,7,0} );
	Image::Pixel dot2 = Image::createPixel( {5,10,9} );
	Image::Pixel dot3 = Image::createPixel( {1,0,7} );
	Image::Pixel dot4 = Image::createPixel( {5,3,0} );
	Image::Pixel dot5 = Image::createPixel( {7,7,4} );
	Image::Pixel dot6 = Image::createPixel( {9,3,0} );
	Image::Pixel dot7 = Image::createPixel( {1,0,7} );
	Image::Pixel dot8 = Image::createPixel( {8,0,7} );
	Image::Pixel dot9 = Image::createPixel( {6,0,4} );

	Matrix::Matrix<Image::Pixel> pxMatrix({
		{dot1, dot2, dot3},
		{dot4, dot5, dot6},
		{dot7, dot8, dot9}
	});
	Matrix::Matrix<Image::Pixel> convolutedPixelMatrix = Matrix::_convoluteUsingMatrix(pxMatrix, convMatrix);
	Logger::logInfo("pxMatrix", "");
	pxMatrix.info();
	Logger::logInfo("convolutedPixelMatrix", "");
	convolutedPixelMatrix.info();

	testEnd(testName);
	return 0;
}

int pixelMatrixToCharTest() {
	std::string testName = "pixelMatrixToCharTest()";
	testStart(testName);

	Matrix::Matrix<unsigned int> kernel({
		{53, 91, 70}, 
		{25, 20, 59}, 
		{54, 57, 78}
	});

	Matrix::Matrix<Image::Pixel>* pxMatrixPtr;
	//Image::ImageAsPixels imageObj("./data/pixel.png");
	Image::ImageAsPixels imageObj("./data/test.jpg");
	pxMatrixPtr = imageObj.getPixels();
	Matrix::Matrix<Image::Pixel> pxMatrix = *pxMatrixPtr;

	Matrix::Matrix<Image::Pixel> convolutedPixelMatrix = Matrix::_convoluteUsingMatrix(pxMatrix, kernel);
	
	/*
	std::cout << "Before:" << std::endl;
	pxMatrix.info();
	std::cout << "After:" << std::endl;
	convolutedPixelMatrix.info();
	*/

	/* unsigned to signed type template
	unsigned int a = 2;
	std::make_signed<unsigned int>::type b = a-5;
	std::cout << "a: " << a << ", b: " << b << std::endl;
	*/
	
	unsigned char* imageData = Matrix::_pixelMatrixToPointers<unsigned char>(&convolutedPixelMatrix);

	Image::ImageStruct testImage;
	testImage = imageObj.getImageStructPropertiesOnly();
	testImage.imgData = imageData;

	Image::writeImageToFile("./data/delme.png", testImage);

	testEnd(testName);
	return 0;
}

int main() {
	std::unordered_map<std::string, bool> performTests = {
		{"imageTest", false},
		{"pixelTest", false},
		{"imageAsPixelsTest", false},
		{"matrixTest", false},
		{"loggerTest", false},
		{"matrixConvolutionTest", false},
		{"pixelMatrixToCharTest", true}
	};

	if (performTests["imageTest"]) {imageTest();}
	if (performTests["pixelTest"]) {pixelTest();}
	if (performTests["imageAsPixelsTest"]) {imageAsPixelsTest();}
	if (performTests["matrixTest"]) {matrixTest();}
	if (performTests["loggerTest"]) {loggerTest();}
	if (performTests["matrixConvolutionTest"]) {matrixConvolutionTest();}
	if (performTests["pixelMatrixToCharTest"]) {pixelMatrixToCharTest();}
	
	return 0;
}
