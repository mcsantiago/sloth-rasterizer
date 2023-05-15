#include "tgaimage.h"
#include "model.h"
#include <iostream>

const TGAColor WHITE = TGAColor(255, 255, 255, 255);
const TGAColor ORANGE = TGAColor(240, 169, 24, 240);
const TGAColor MAGENTA = TGAColor(227, 34, 108, 227);
const int WIDTH = 200;
const int HEIGHT = 200;

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

void triangle(Vec2i *points, TGAImage &image, const TGAColor &color) {
    Vec3i a = Vec3i(points[0]);
    Vec3i b = Vec3i(points[1]);
    Vec3i c = Vec3i(points[2]);
    Vec3i ab = a - b;
    Vec3i bc = b - c;
    Vec3i ca = c - a;

    // Create the bounding box
    Vec2i bboxmin = Vec2i(image.get_width() - 1, image.get_height() - 1);
    Vec2i bboxmax = Vec2i(0, 0);
    Vec2i maxClamp = Vec2i(image.get_width() - 1, image.get_height() - 1);

    for (int i = 0; i < 3; i++) {
        bboxmin.x = std::max(0, std::min(bboxmin.x, points[i].x));
        bboxmin.y = std::max(0, std::min(bboxmin.y, points[i].y));

        bboxmax.x = std::min(maxClamp.x, std::max(bboxmax.x, points[i].x));
        bboxmax.y = std::min(maxClamp.y, std::max(bboxmax.y, points[i].y));
    }

    // Go through each horizontal line and check if each point x in the line is in the triangle
    for (int y = bboxmin.y; y <= bboxmax.y; y++) {
        for (int x = bboxmin.x; x <= bboxmax.x; x++) {
            // Create AP, BP, CP vectors
            Vec3i ap = a - Vec3i(x, y, 0);
            Vec3i bp = b - Vec3i(x, y, 0);
            Vec3i cp = c - Vec3i(x, y, 0);

            Vec3i cross1 = ab.cross(ap);
            Vec3i cross2 = bc.cross(bp);
            Vec3i cross3 = ca.cross(cp);

            if ((cross1.z > 0 && cross2.z > 0 && cross3.z > 0) ||
                (cross1.z < 0 && cross2.z < 0 && cross3.z < 0)) {
                image.set(x, y, color);
            }
        }
    }
}

void drawModelMesh(Model *model, TGAImage &image, TGAColor) {
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
}

int main(int argc, char **argv) {
	TGAImage image(WIDTH, HEIGHT, TGAImage::RGBA);
    Vec2i trianglePoints[3] = {Vec2i(2,3), Vec2i(45, -30), Vec2i(369, 72)};
//    auto *model = new Model("../obj/test_head.obj");
//    drawModelMesh(model, image, WHITE);
    triangle(trianglePoints, image, ORANGE);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
    std::cout << "File successfully written: output.tga" << std::endl;
	return 0;
}
