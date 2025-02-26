#include "geometry.hpp"
#include "svg_utils.hpp"
#include <iostream>
#include <vector>

int main() {
    // Initialize the points for the base object
    std::vector<Point> points = {
        {100, 100}, // Point 1
        {200, 100}, // Point 2
        {200, 200}, // Point 3
        {100, 200}  // Point 4
    };

    // Create the base object
    Object baseObject;
    baseObject.points = points; // Assign the points vector
    baseObject.color = "blue"; // Set the color

    // Create the canvas
    Canvas canvas;
    canvas.width = 800; // Set canvas width
    canvas.height = 600; // Set canvas height
    
    // Create a vector with the base object and assign it to canvas.baseObject
    std::vector<Object> objects;
    objects.push_back(baseObject);
    canvas.baseObject = objects;

    canvas.rows = 2; // Set number of rows
    canvas.cols = 3; // Set number of columns

    // Define transformations
    std::vector<std::pair<std::string, double>> transforms = {
        {"rotate", 45},    // Example transformation: rotate by 45 degrees
        {"scale", 1.2}     // Example transformation: scale by a factor of 1.2
    };

    // Generate the SVG with transformations
    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    std::cout << svg << std::endl; // Output SVG to console (or save to a file)
    return 0;
}