#pragma once

#include <vector>
#include <string>
#include "Color.h"

struct Framebuffer {
    std::vector<Color> pixels;
    int screenWidth;
    int screenHeight;
    Color defaultColor;

    Framebuffer(int width, int height)
        : screenWidth(width), screenHeight(height), defaultColor(0, 0, 0) {
        pixels.resize(width * height, defaultColor);
    }

    void setDefaultColor(Color color) {
        this->defaultColor = color;
    }

    void setPixelBGR(int x, int y, const Color& color) {
        if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
            pixels[(screenHeight - y - 1) * screenWidth + x] = color;
        }
    }

    void setPixelRGB(int x, int y, const Color& color) {
        if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
            Color newColor = Color(color.blue, color.green, color.red);
            pixels[(screenHeight - y - 1) * screenWidth + x] = newColor;
        }
    }

    Color getPixel(int x, int y) const {
        if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
            return pixels[(screenHeight - y - 1) * screenWidth + x];
        }
        return defaultColor; // Default color if pixel coordinates are out of bounds
    }

    void clear() {
        std::fill(pixels.begin(), pixels.end(), defaultColor);
    }

    int getWidth() const {
        return screenWidth;
    }

    int getHeight() const {
        return screenHeight;
    }
};
