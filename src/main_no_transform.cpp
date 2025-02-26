#include "canvas.hpp"
#include <iostream>

int main() {
    // Initialize the points for the base object
    std::vector<Point> points = {
        {100, 100},
        {200, 100},
        {200, 200},
        {100, 200}
    };

    // Create the base object
    Object baseObject = {points, "blue"};

    // Create the canvas
    Canvas canvas = {
        800, 600, // width, height
        baseObject, // baseObject
        3, 2 // rows, cols
    };

    // Generate the SVG without transformations
    std::string svg = canvas_composed_to_svg(canvas);
    std::cout << svg << std::endl; // Output SVG to console (or save to a file)
    return 0;
}