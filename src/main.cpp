#include <iostream>
#include <algorithm>    // for std::sort
#include "Framebuffer.h"
#include "BMPWriter.h"
#include "Vertex2.h"

// Framebuffer dimensions
const int WIDTH = 800;
const int HEIGTH = 600;

// Set the current color
Color currentColor = Color(0, 255, 0);     // Green

// Default colors
const Color WHITE = Color(255, 255, 255);
const Color BLACK = Color(0, 0, 0);
const Color RED = Color(255, 0, 0);
const Color GREEN = Color(0, 255, 0);
const Color BLUE = Color(0, 0, 255);
const Color YELLOW = Color(255, 255, 0);

// Create the framebuffer
Framebuffer framebuffer(WIDTH, HEIGTH);


void setCurrentColor(Color color) {
    currentColor = color;
}

void point(Vertex2 point) {
    framebuffer.setPixelRGB(point.x, point.y, currentColor);
}

void line(const Vertex2& start, const Vertex2& end) {
    int x0 = static_cast<int>(start.x);
    int y0 = static_cast<int>(start.y);
    int x1 = static_cast<int>(end.x);
    int y1 = static_cast<int>(end.y);

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        point(Vertex2{x0, y0});

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawPolygon(const std::vector<Vertex2>& points) {
    if (points.size() < 2) {
        return; // A polygon requires at least two points
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        line(points[i], points[i + 1]);
    }
    // Connect the last point to the first point to close the polygon
    line(points.back(), points.front());
}

void floodFill(int x, int y, const Color& fillColor, const Color& targetColor) {
    if (x < 0 || x >= framebuffer.getWidth() || y < 0 || y >= framebuffer.getHeight()) {
        return;
    }

    Color currentColor = framebuffer.getPixel(x, y);
    if (currentColor != targetColor) {
        return;
    }

    // point(Vertex2{x, y});
    framebuffer.setPixelRGB(x, y, fillColor);

    floodFill(x + 1, y, fillColor, targetColor);
    floodFill(x - 1, y, fillColor, targetColor);
    floodFill(x, y + 1, fillColor, targetColor);
    floodFill(x, y - 1, fillColor, targetColor);
}

void fillPolygon(const std::vector<Vertex2>& points, const Color& fillColor) {
    if (points.size() < 3) {
        return; // A polygon requires at least three points
    }

    // Find a seed point inside the polygon (e.g., the centroid)
    float sumX = 0.0f, sumY = 0.0f;
    for (const Vertex2& point : points) {
        sumX += point.x;
        sumY += point.y;
    }
    int seedX = static_cast<int>(sumX / points.size());
    int seedY = static_cast<int>(sumY / points.size());

    Color targetColor = framebuffer.getPixel(seedX, seedY);

    floodFill(seedX, seedY, fillColor, targetColor);
}

void renderBuffer() {
    // Write the framebuffer to a BMP file
    writeBMP("../out.bmp", framebuffer);
}

void render() {
    // Clear the buffer
    framebuffer.clear();

    // Polygon 4
    std::vector<Vertex2> polygon4 = {
        Vertex2(413, 177), Vertex2(448, 159), Vertex2(502, 88), Vertex2(553, 53), Vertex2(535, 36), Vertex2(676, 37), Vertex2(660, 52),
        Vertex2(750, 145), Vertex2(761, 179), Vertex2(672, 192), Vertex2(659, 214), Vertex2(615, 214), Vertex2(632, 230), Vertex2(580, 230),
        Vertex2(597, 215), Vertex2(552, 214), Vertex2(517, 144), Vertex2(466, 180)
    };

    // Polygon 5
    std::vector<Vertex2> polygon5 = {
        Vertex2(682, 175),
        Vertex2(708, 120),
        Vertex2(735, 148),
        Vertex2(739, 170)
    };

    setCurrentColor(WHITE);

    drawPolygon(polygon4);
    fillPolygon(polygon4, GREEN);
    
    drawPolygon(polygon5);
    fillPolygon(polygon5, BLACK);

    // Render the buffer
    renderBuffer();
}


int main() {
    // Render the framebuffer
    render();

    return 0;
}
