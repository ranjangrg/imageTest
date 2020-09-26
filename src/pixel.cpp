#include "./headers/image/pixel.h"

namespace Image {
	void pixelInfo(const Pixel& p) {
		std::cout << "[INFO] Pixel: (r, g, b, a) => (";
		std::cout << (int)(p.r) << ", ";
		std::cout << (int)(p.g) << ", ";
		std::cout << (int)(p.b) << ", ";
		std::cout << (int)(p.a) << ")" << std::endl;
	}
}