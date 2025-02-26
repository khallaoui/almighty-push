#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#include "canvas.hpp"
#include <string>
#include <vector>

// Simple transformation structure
struct Transform {
    std::string type;  // "translate", "rotate", or "scale"
    double value;
    Transform* next = nullptr;
};

// Composed transformation structure
struct ListTransform {
    Transform* head = nullptr;
    
    void add(const std::string& type, double value);
    void remove(const std::string& type);
    void clear();
    ~ListTransform();
};

// Basic transformations
void translate_object(Object& obj, double tx, double ty);
void translate_composedObject(std::vector<Object>& objects, double tx, double ty);
void scale_object(Object& obj, double k);
void scale_composedObject(std::vector<Object>& objects, double k);
void rotate_object(Object& obj, double angle, Point center);
void rotate_composedObject(std::vector<Object>& objects, double angle, Point center);

// Advanced transformations
void apply_transform(Object& obj, const Transform& transform, Point center);
void apply_list_transform(Object& obj, const ListTransform& transforms, Point center);
void apply_random_transforms(Object& obj, const std::vector<Transform>& possible_transforms, Point center);

#endif // GEOMETRY_HPP