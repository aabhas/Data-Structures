#ifndef image_H
#define image_H
#include "png.h"
#include "rgbapixel.h"

class Image : public PNG{

		public:
		void flipleft();
		void adjustbrightness(int r, int g, int b);
		void invertcolors();
			};
#endif

