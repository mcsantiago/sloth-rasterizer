#include "tgaimage.h"
#include "model.h"
#include <iostream>

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const int WIDTH = 800;
const int HEIGHT = 600;

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (std::abs(x1-x0) < std::abs(y1-y0)) {
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
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGBA);
    auto *model = new Model("../obj/test_head.obj");

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*WIDTH/2.;
            int y0 = (v0.y+1.)*HEIGHT/2.;
            int x1 = (v1.x+1.)*WIDTH/2.;
            int y1 = (v1.y+1.)*HEIGHT/2.;
            line(x0, y0, x1, y1, image, WHITE);
        }
    }
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
    std::cout << "File successfully written: output.tga" << std::endl;
	return 0;
}
