#include "canvas.hpp"
#include <fstream>
#include <iostream>
#include <vector>

// Helper function to create a square
Object create_square(double x, double y, double size, const std::string& color) {
    Object obj;
    obj.points = {
        {x, y},
        {x + size, y},
        {x + size, y + size},
        {x, y + size}
    };
    obj.color = color;
    return obj;
}

// Create a complex object (4 centered squares)
std::vector<Object> create_complex_square(double centerX, double centerY) {
    std::vector<Object> objects;
    
    // Outer square (blue)
    objects.push_back(create_square(centerX - 60, centerY - 60, 120, "blue"));
    
    // Middle squares (red)
    objects.push_back(create_square(centerX - 40, centerY - 40, 80, "red"));
    objects.push_back(create_square(centerX - 30, centerY - 30, 60, "red"));
    
    // Inner square (blue)
    objects.push_back(create_square(centerX - 20, centerY - 20, 40, "blue"));
    
    return objects;
}

int main() {
    // Create the base complex object
    std::vector<Object> complexObject = create_complex_square(100, 100);
    
    // Create the canvas
    Canvas canvas;
    canvas.width = 800;
    canvas.height = 600;
    canvas.baseObject = complexObject;
    canvas.rows = 2;      // 2 rows
    canvas.cols = 3;      // 3 columns

    // Generate the SVG
    std::string svg = canvas_composed_to_svg(canvas);

    // Create HTML
    std::string html = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Vera Molnár Style Composition</title>
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

    // Save the HTML
    std::ofstream file("vera_molnar_composition.html");
    if (file.is_open()) {
        file << html;
        file.close();
        std::cout << "Composition saved as 'vera_molnar_composition.html'" << std::endl;
    } else {
        std::cerr << "Error: Unable to save HTML file." << std::endl;
    }

    return 0;
}