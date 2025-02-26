#include "../include/canvas.hpp"
#include "../include/geometry.hpp"
#include "../include/svg_utils.hpp"
#include <fstream>
#include <iostream>
#include <direct.h> // For _mkdir on Windows
#include <string>
#include <vector>
#include <cmath>

// Forward declarations
void save_to_html(const std::string& svg, const std::string& title);

// Create a square
Object create_square(double size, const std::string& color) {
    Object obj;
    obj.points = {
        {0, 0},
        {size, 0},
        {size, size},
        {0, size}
    };
    obj.color = color;
    return obj;
}

// Create a triangle
Object create_triangle(double size, const std::string& color) {
    Object obj;
    obj.points = {
        {size/2, 0},
        {size, size},
        {0, size}
    };
    obj.color = color;
    return obj;
}

// Create a pentagon
Object create_pentagon(double size, const std::string& color) {
    Object obj;
    const double angle = 2 * M_PI / 5;
    for (int i = 0; i < 5; ++i) {
        obj.points.push_back({
            size/2 + size/2 * cos(i * angle - M_PI/2),
            size/2 + size/2 * sin(i * angle - M_PI/2)
        });
    }
    obj.color = color;
    return obj;
}

// Create more shapes
Object create_hexagon(double size, const std::string& color) {
    Object obj;
    const double angle = 2 * M_PI / 6;
    for (int i = 0; i < 6; ++i) {
        obj.points.push_back({
            size/2 + size/2 * cos(i * angle - M_PI/2),
            size/2 + size/2 * sin(i * angle - M_PI/2)
        });
    }
    obj.color = color;
    return obj;
}

Object create_star(double size, const std::string& color) {
    Object obj;
    const int points = 5;
    const double outerRadius = size/2;
    const double innerRadius = size/4;
    
    for (int i = 0; i < points * 2; ++i) {
        double radius = (i % 2 == 0) ? outerRadius : innerRadius;
        double angle = i * M_PI / points;
        obj.points.push_back({
            size/2 + radius * cos(angle - M_PI/2),
            size/2 + radius * sin(angle - M_PI/2)
        });
    }
    obj.color = color;
    return obj;
}

std::vector<Object> create_vera_molnar_squares(double centerX, double centerY) {
    std::vector<Object> objects;
    
    // Outer square (blue)
    objects.push_back(create_square(60, "blue"));  // Larger square
    
    // Middle squares (red) that remain constant
    objects.push_back(create_square(40, "red"));   // Medium square
    objects.push_back(create_square(30, "red"));   // Smaller medium square
    
    // Inner square (blue)
    objects.push_back(create_square(20, "blue"));  // Smallest square
    
    // Center all squares
    for (auto& obj : objects) {
        for (auto& point : obj.points) {
            point.x += centerX - obj.points[0].x/2;
            point.y += centerY - obj.points[0].y/2;
        }
    }
    
    return objects;
}

void example1_rotating_squares() {
    Canvas canvas;
    canvas.width = 800;
    canvas.height = 600;
    
    // Create a vector and add the square to it
    std::vector<Object> objects;
    objects.push_back(create_square(50, "blue"));
    canvas.baseObject = objects;
    
    canvas.rows = 4;
    canvas.cols = 6;

    std::vector<std::pair<std::string, double>> transforms = {
        {"rotate", 45},
        {"scale", 0.8}
    };

    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    save_to_html(svg, "rotating_squares.html");
}

void example2_growing_triangles() {
    Canvas canvas;
    canvas.width = 800;
    canvas.height = 600;
    
    std::vector<Object> objects;
    objects.push_back(create_triangle(60, "red"));
    canvas.baseObject = objects;
    
    canvas.rows = 3;
    canvas.cols = 5;

    std::vector<std::pair<std::string, double>> transforms = {
        {"scale", 1.5},
        {"rotate", 30}
    };

    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    save_to_html(svg, "growing_triangles.html");
}

void example3_dancing_pentagons() {
    Canvas canvas;
    canvas.width = 1000;
    canvas.height = 800;
    
    std::vector<Object> objects;
    objects.push_back(create_pentagon(70, "purple"));
    canvas.baseObject = objects;
    
    canvas.rows = 4;
    canvas.cols = 4;

    std::vector<std::pair<std::string, double>> transforms = {
        {"rotate", 72},
        {"scale", 1.2},
        {"translate", 20}
    };

    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    save_to_html(svg, "dancing_pentagons.html");
}

void example4_morphing_hexagons() {
    Canvas canvas;
    canvas.width = 800;
    canvas.height = 600;
    
    // Create a vector and add the hexagon to it
    std::vector<Object> objects;
    objects.push_back(create_hexagon(50, "green"));
    canvas.baseObject = objects;  // Now assigning vector to vector
    
    canvas.rows = 4;
    canvas.cols = 5;

    std::vector<std::pair<std::string, double>> transforms = {
        {"rotate", 60},
        {"scale", 0.9},
        {"translate", 10}
    };

    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    save_to_html(svg, "morphing_hexagons.html");
}

void example5_dancing_stars() {
    Canvas canvas;
    canvas.width = 1000;
    canvas.height = 800;
    
    // Create a vector and add the star to it
    std::vector<Object> objects;
    objects.push_back(create_star(60, "orange"));
    canvas.baseObject = objects;  // Now assigning vector to vector
    
    canvas.rows = 5;
    canvas.cols = 5;

    std::vector<std::pair<std::string, double>> transforms = {
        {"rotate", 36},
        {"scale", 1.1},
        {"translate", 15}
    };

    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    save_to_html(svg, "dancing_stars.html");
}

void example_vera_molnar() {
    Canvas canvas;
    canvas.width = 800;
    canvas.height = 600;
    
    // Create the complex object
    std::vector<Object> objects = create_vera_molnar_squares(0, 0);
    canvas.baseObject = objects;
    
    canvas.rows = 2;  // 2 rows as specified
    canvas.cols = 3;  // 3 columns as specified

    // Apply transformations
    std::vector<std::pair<std::string, double>> transforms = {
        {"rotate", 45},    // 45-degree rotation
        {"scale", 1.2}     // 20% size increase
    };

    std::string svg = canvas_transform_composed_to_svg(canvas, transforms);
    save_to_html(svg, "vera_molnar_transformed.html");
}

void save_to_html(const std::string& svg, const std::string& title) {
    std::string html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>)" + title + R"(</title>
    <style>
        body { display: flex; justify-content: center; align-items: center; height: 100vh; margin: 0; }
        div { border: 1px solid #ccc; padding: 20px; }
    </style>
</head>
<body>
    <div>
)" + svg + R"(
    </div>
</body>
</html>
)";

    std::ofstream file("transformed_shape.html");
    if (file.is_open()) {
        file << html;
        file.close();
        std::cout << "Transformed shape saved as 'transformed_shape.html'" << std::endl;
    }
}

int main() {
    example1_rotating_squares();
    example2_growing_triangles();
    example3_dancing_pentagons();
    example4_morphing_hexagons();
    example5_dancing_stars();
    example_vera_molnar();
    return 0;
}