#ifndef CANVAS_HPP

///
//test'''yjy
// git test
//3aaa

#define CANVAS_HPP

#include <vector>
#include <string>

// Basic structures
struct Point {
    double x, y;
};

struct Object {
    std::vector<Point> points;
    std::string color;
};

struct Canvas {
    int width, height;
    std::vector<Object> baseObject;
    int rows, cols;
};

#endif // CANVAS_HPP