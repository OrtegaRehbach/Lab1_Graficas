#pragma once

#include <iostream>
#include <fstream>
#include <cstdint>
#include "Framebuffer.h"

void writeBMP(const std::string& filename, Framebuffer& framebuffer) {
    int width = framebuffer.getWidth();
    int height = framebuffer.getHeight();

    // Create the file in binary mode
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to create BMP file: " << filename << std::endl;
        return;
    }

    // Clear the framebuffer
    // framebuffer.clear();

    // Write the file header
    char fileHeader[14] = {
        'B', 'M',       // Signature (BM)
        0, 0, 0, 0,     // File size (placeholder)
        0, 0,           // Reserved
        0, 0,           // Reserved
        54, 0, 0, 0     // Offset to pixel data
    };
    file.write(fileHeader, 14);

    // Write the image header
    char imageHeader[40] = {
        40, 0, 0, 0,    // Size of image header
        0, 0, 0, 0,     // Width of the image (placeholder)
        0, 0, 0, 0,     // Height of the image (placeholder)
        1, 0,           // Number of color planes
        24, 0,          // Bits per pixel
        0, 0, 0, 0,     // Compression method (uncompressed)
        0, 0, 0, 0,     // Image size (placeholder)
        0, 0, 0, 0,     // Horizontal resolution
        0, 0, 0, 0,     // Vertical resolution
        0, 0, 0, 0,     // Number of colors in the color palette
        0, 0, 0, 0      // Number of important colors
    };
    *reinterpret_cast<int*>(&imageHeader[4]) = width;
    *reinterpret_cast<int*>(&imageHeader[8]) = height;
    *reinterpret_cast<int*>(&imageHeader[20]) = width * height * 3;
    file.write(imageHeader, 40);

    // Write the pixel data (bottom-up)
    // for (int y = height - 1; y >= 0; --y) {
    //     for (int x = 0; x < width; ++x) {
    //         const Color& pixel = framebuffer.getPixel(x, y);
    //         file.write(reinterpret_cast<const char*>(&pixel), 3);
    //     }
    // }

    // Write the pixel data (top-down)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Color pixel = framebuffer.getPixel(x, y);
            file.write(reinterpret_cast<const char*>(&pixel), 3);
        }
    }

    // Close the file
    file.close();

    std::cout << "BMP file created successfully: " << filename << std::endl;
}
