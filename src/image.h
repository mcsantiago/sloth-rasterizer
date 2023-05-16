//
// Created by Matthew on 5/16/23.
//

#ifndef SLOTH_RENDERER_IMAGE_H
#define SLOTH_RENDERER_IMAGE_H

#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "include/stb_image_write.h"

struct Color {
    Color(int r, int g, int b, int a)
    : r(r), g(g), b(b), a(a) {}

    unsigned int r;
    unsigned int g;
    unsigned int b;
    unsigned int a;
};

enum Channel {
    RGB = 3,
    RGBA = 4
};

class Image {
private:
    int width, height;
    Channel channels;
    unsigned char* data;

public:
    Image(int width, int height, Channel channels)
        : width(width), height(height), channels(channels)
    {
        data = new unsigned char[width * height * static_cast<int>(channels)];
    }

    ~Image() {
        delete [] data;
    }

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    void setPixel(int x, int y, Color color) {
        int index = (y * width + x) * channels;
        data[index + 0] = color.r;
        data[index + 1] = color.g;
        data[index + 2] = color.b;
        data[index + 3] = color.a;
    }

    void flipVertically() {
        int rowSize = width * static_cast<int>(channels);
        auto tempRow = new unsigned char[rowSize];

        for (int y = 0; y < height / 2; ++y) {
            int topRowIndex = y * rowSize;
            int bottomRowIndex = (height - 1 - y) * rowSize;

            // Swap rows using a temporary row buffer
            std::memcpy(tempRow, data + topRowIndex, rowSize);
            std::memcpy(data + topRowIndex, data + bottomRowIndex, rowSize);
            std::memcpy(data + bottomRowIndex, tempRow, rowSize);
        }

        delete[] tempRow;
    }

    void writeToDiskAsPNG(const std::string &filename) {
        stbi_write_png(filename.c_str(), width, height, channels, data, width * channels);
    }
};

#endif //SLOTH_RENDERER_IMAGE_H
