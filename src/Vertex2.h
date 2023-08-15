#pragma once

struct Vertex2 {
    float x;
    float y;

    Vertex2() : x(0.0f), y(0.0f) {}
    Vertex2(float x_, float y_) : x(x_), y(y_) {}
    Vertex2(int x_, int y_) : x(static_cast<float>(x_)), y(static_cast<float>(y_)) {}
};