#include <iostream>
#include "model.h"
#include "image.h"

const Color WHITE = Color(255, 255, 255, 255);
const Color ORANGE = Color(240, 169, 24, 240);
const Color MAGENTA = Color(255, 255, 255, 227);

const int WIDTH = 800;
const int HEIGHT = 600;

void line(int x0, int y0, int x1, int y1, Image &image, Color color) {
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
			image.setPixel(y, x, color);
		} else {
			image.setPixel(x, y, color);
		}

		if (p < 0) {
			p += 2 * dy;
		} else {
			p += (2*dy - 2*dx);
			y += (y1 > y0) ? 1 : -1;
		}
	}
}

void triangle(Vec2i *points, Image &image, const Color &color) {
    Vec3i a = Vec3i(points[0]);
    Vec3i b = Vec3i(points[1]);
    Vec3i c = Vec3i(points[2]);
    Vec3i ab = a - b;
    Vec3i bc = b - c;
    Vec3i ca = c - a;

    // Create the bounding box
    Vec2i bboxmin = Vec2i(image.getWidth() - 1, image.getHeight() - 1);
    Vec2i bboxmax = Vec2i(0, 0);
    Vec2i maxClamp = Vec2i(image.getWidth() - 1, image.getHeight() - 1);

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

            Vec3i cross1 = ab^ap;
            Vec3i cross2 = bc^bp;
            Vec3i cross3 = ca^cp;

            if ((cross1.z > 0 && cross2.z > 0 && cross3.z > 0) ||
                (cross1.z < 0 && cross2.z < 0 && cross3.z < 0)) {
                image.setPixel(x, y, color);
            }
        }
    }
}

void drawModelMesh(Model *model, Image &image, Color color) {
    Vec3f light_dir(0, 0, -1.);

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x+1.)*WIDTH/2., (v.y+1)*HEIGHT/2.);
            world_coords[j] = v;
        }
        Vec3f normal = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        normal.normalize();
        float intensity = normal*light_dir;
        if (intensity > 0) {
            triangle(screen_coords, image, Color(intensity*255, intensity*255, intensity*255, 255));
        }
    }
}

int main(int argc, char **argv) {
    Image image(WIDTH, HEIGHT, Channel::RGBA);
    auto *model = new Model("../obj/test_head.obj");
    drawModelMesh(model, image, WHITE);
	image.flipVertically(); // i want to have the origin at the left bottom corner of the image
	image.writeToDiskAsPNG("output.png");
    std::cout << "File successfully written: output.png" << std::endl;
	return 0;
}
