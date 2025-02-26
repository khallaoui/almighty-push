#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "canvas.hpp" // Include canvas.hpp to access Object and Point
#include <string>
#include <vector>
#include <random>  // Add for random number generation

// Translate an object by (tx, ty)
void translate_object(Object& obj, double tx, double ty);

// Translate a composed object (a vector of objects) by (tx, ty)
void translate_composedObject(std::vector<Object>& objects, double tx, double ty);

// New function for A6.a
std::string canvas_list_transform_simpleObject_to_svg(
    const Canvas& canvas,
    const std::vector<Transform>& possible_transforms,
    int objectIndex = -1  // -1 means apply to all objects
);

#endif // GEOMETRY_HPP

#ifndef SVG_UTILS_HPP
#define SVG_UTILS_HPP

#include "canvas.hpp"
#include "geometry.hpp"
#include <string>
#include <vector>

// Basic SVG functions
std::string point_to_svg(const Point& p);
std::string object_to_svg(const Object& obj);

// Canvas to SVG conversion functions
std::string canvas_composed_to_svg(const Canvas& canvas);
std::string canvas_transform_composed_to_svg(
    const Canvas& canvas,
    const std::vector<std::pair<std::string, double>>& transforms
);
std::string canvas_list_transform_simpleObject_to_svg(
    const Canvas& canvas,
    const std::vector<Transform>& possible_transforms,
    int objectIndex = -1
);

// HTML helper
std::string create_html_wrapper(const std::string& svg, const std::string& title);

#endif // SVG_UTILS_HPP