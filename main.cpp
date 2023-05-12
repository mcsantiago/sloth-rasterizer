#include "tgaimage.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (std::abs(x1-x0) < std::abs(y1-y0)) {
		std::cout << "steep" << std::endl;
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);
	int p = 2*dx - dy;
	int y = y0;
	for (int x = x0; x < x1; x++) {
		if (steep) {
			image.set(y, x, color);
		} else {
			image.set(x, y, color);
		}

		if (p < 0) {
			p += 2 * dy;
		} else {
			p += (2*dy - 2*dx);
			y += (y1 > y0) ? 1 : -1;
		}
	}
}

int main(int argc, char **argv) {
	TGAImage image(100, 100, TGAImage::RGBA);
	line(0, 0, 100, 100, image, TGAColor(255, 255, 255, 255));
	line(0, 0, 100, 50, image, TGAColor(255, 255, 255, 255));
	line(0, 0, 50, 100, image, TGAColor(255, 255, 255, 255));
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}
