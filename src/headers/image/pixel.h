#ifndef __PIXEL_H
#define __PIXEL_H

#include "../basic.h"

namespace Image {
	typedef struct pixel {
		unsigned char r, g, b, a;
	} Pixel;

	void pixelInfo(const Pixel& p);
}

#endif