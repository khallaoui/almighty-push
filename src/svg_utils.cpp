#include "svg_utils.hpp"
#include <sstream>
#include <cmath>
#include <random>

// Helper function to convert a point to an SVG string
std::string point_to_svg(const Point& p) {
    return std::to_string(p.x) + "," + std::to_string(p.y);
}

// Function to generate SVG for a single object
std::string object_to_svg(const Object& obj) {
    std::ostringstream svg;
    svg << "<polygon points=\"";
    for (const auto& point : obj.points) {
        svg << point_to_svg(point) << " ";
    }
    svg << "\" fill=\"" << obj.color << "\" />\n";
    return svg.str();
}

// Function to generate SVG for a canvas without transformations
std::string canvas_composed_to_svg(const Canvas& canvas) {
    std::ostringstream svg;
    svg << "<svg width=\"" << canvas.width << "\" height=\"" << canvas.height 
        << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    double spacingX = canvas.width / (canvas.cols + 1);
    double spacingY = canvas.height / (canvas.rows + 1);

    for (int i = 0; i < canvas.rows; ++i) {
        for (int j = 0; j < canvas.cols; ++j) {
            // Create a copy of the complex object
            std::vector<Object> objects = canvas.baseObject;
            
            // Translate the complex object to its position
            double tx = (j + 1) * spacingX;
            double ty = (i + 1) * spacingY;
            translate_composedObject(objects, tx, ty);

            // Add all objects to SVG
            for (const auto& obj : objects) {
                svg << object_to_svg(obj);
            }
        }
    }

    svg << "</svg>";
    return svg.str();
}

// Function to generate SVG for a canvas with transformations
std::string canvas_transform_composed_to_svg(const Canvas& canvas, const std::vector<std::pair<std::string, double>>& transforms) {
    std::ostringstream svg;
    svg << "<svg width=\"" << canvas.width << "\" height=\"" << canvas.height 
        << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    double spacingX = canvas.width / (canvas.cols + 1);
    double spacingY = canvas.height / (canvas.rows + 1);

    for (int i = 0; i < canvas.rows; ++i) {
        for (int j = 0; j < canvas.cols; ++j) {
            // Create a copy of the base objects
            std::vector<Object> objects = canvas.baseObject;

            // Calculate center position for this grid cell
            double tx = (j + 1) * spacingX;
            double ty = (i + 1) * spacingY;
            
            // First translate to position
            translate_composedObject(objects, tx, ty);

            // Apply each transformation
            for (const auto& transform : transforms) {
                if (transform.first == "translate") {
                    translate_composedObject(objects, transform.second, transform.second);
                } 
                else if (transform.first == "rotate") {
                    // Calculate center of the object group
                    double centerX = tx;
                    double centerY = ty;
                    
                    for (auto& obj : objects) {
                        for (auto& point : obj.points) {
                            // Convert angle to radians
                            double rad = transform.second * M_PI / 180.0;
                            
                            // Translate point to origin
                            double dx = point.x - centerX;
                            double dy = point.y - centerY;
                            
                            // Rotate point
                            double newX = dx * cos(rad) - dy * sin(rad);
                            double newY = dx * sin(rad) + dy * cos(rad);
                            
                            // Translate back
                            point.x = centerX + newX;
                            point.y = centerY + newY;
                        }
                    }
                } 
                else if (transform.first == "scale") {
                    // Calculate center of the object group
                    double centerX = tx;
                    double centerY = ty;
                    
                    for (auto& obj : objects) {
                        for (auto& point : obj.points) {
                            // Scale point relative to center
                            point.x = centerX + (point.x - centerX) * transform.second;
                            point.y = centerY + (point.y - centerY) * transform.second;
                        }
                    }
                }
            }

            // Add transformed objects to SVG
            for (const auto& obj : objects) {
                svg << object_to_svg(obj);
            }
        }
    }

    svg << "</svg>";
    return svg.str();
}

std::string canvas_list_transform_simpleObject_to_svg(
    const Canvas& canvas,
    const std::vector<Transform>& possible_transforms,
    int objectIndex
) {
    std::ostringstream svg;
    svg << "<svg width=\"" << canvas.width << "\" height=\"" << canvas.height 
        << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    double spacingX = canvas.width / (canvas.cols + 1);
    double spacingY = canvas.height / (canvas.rows + 1);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2); // 0, 1, or 2 transformations

    for (int i = 0; i < canvas.rows; ++i) {
        for (int j = 0; j < canvas.cols; ++j) {
            std::vector<Object> cell_objects = canvas.baseObject;
            Point center{(j + 1) * spacingX, (i + 1) * spacingY};
            
            // Translate the whole group to position
            translate_composedObject(cell_objects, center.x, center.y);

            // Apply random transformations to specific object or all objects
            int numTransforms = dis(gen);
            if (objectIndex >= 0 && objectIndex < cell_objects.size()) {
                // Apply to specific object
                for (int t = 0; t < numTransforms; ++t) {
                    apply_transform(cell_objects[objectIndex], 
                                  possible_transforms[t % possible_transforms.size()], 
                                  center);
                }
            } else {
                // Apply to all objects
                for (auto& obj : cell_objects) {
                    for (int t = 0; t < numTransforms; ++t) {
                        apply_transform(obj, 
                                      possible_transforms[t % possible_transforms.size()], 
                                      center);
                    }
                }
            }

            // Add all objects to SVG
            for (const auto& obj : cell_objects) {
                svg << object_to_svg(obj);
            }
        }
    }

    svg << "</svg>";
    return svg.str();
}

std::string create_html_wrapper(const std::string& svg, const std::string& title) {
    return R"(
<!DOCTYPE html>
<html>
<head>
    <title>)" + title + R"(</title>
</head>
<body>
)" + svg + R"(
</body>
</html>
)";
}