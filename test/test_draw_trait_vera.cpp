#include "../include/canvas.hpp"
#include "../include/geometry.hpp"
#include "../include/svg_utils.hpp"
#include <fstream>
#include <iostream>

// Create Vera Molnár style squares
std::vector<Object> create_vera_squares() {
    std::vector<Object> objects;
    objects.push_back(create_square(0, 0, 60, "blue"));    // Outer square
    objects.push_back(create_square(10, 10, 40, "red"));   // Middle square 1
    objects.push_back(create_square(15, 15, 30, "red"));   // Middle square 2
    objects.push_back(create_square(20, 20, 20, "blue"));  // Inner square
    return objects;
}

void test_vera_simple() {
    Canvas canvas;
    canvas.width = 800;
    canvas.height = 600;
    canvas.baseObject = create_vera_squares();
    canvas.rows = 2;
    canvas.cols = 3;

    std::vector<Transform> transforms = {
        {"rotate", 45},
        {"scale", 0.8},
        {"rotate", 90}
    };

    // Test 1: Transform all objects
    std::string svg1 = canvas_list_transform_simpleObject_to_svg(canvas, transforms);
    std::ofstream file1("vera_all_objects.html");
    if (file1.is_open()) {
        file1 << create_html_wrapper(svg1, "Vera Molnar - All Objects");
        file1.close();
    }

    // Test 2: Transform only the inner square (index 3)
    std::string svg2 = canvas_list_transform_simpleObject_to_svg(canvas, transforms, 3);
    std::ofstream file2("vera_inner_square.html");
    if (file2.is_open()) {
        file2 << create_html_wrapper(svg2, "Vera Molnar - Inner Square");
        file2.close();
    }
}

int main() {
    test_vera_simple();
    return 0;
}
