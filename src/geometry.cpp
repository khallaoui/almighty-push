#include "geometry.hpp"
#include <cmath>
#include <random>

// Translate an object by (tx, ty)
void translate_object(Object& obj, double tx, double ty) {
    for (auto& point : obj.points) {
        point.x += tx;
        point.y += ty;
    }
}

// Translate a composed object (a vector of objects) by (tx, ty)
void translate_composedObject(std::vector<Object>& objects, double tx, double ty) {
    for (auto& obj : objects) {
        translate_object(obj, tx, ty);
    }
}

// Scale an object by a factor of k
void scale_object(Object& obj, double k) {
    // Calculate the centroid (barycenter) of the object
    double xG = 0, yG = 0;
    for (const auto& point : obj.points) {
        xG += point.x;
        yG += point.y;
    }
    xG /= obj.points.size();
    yG /= obj.points.size();

    // Apply scaling transformation
    for (auto& point : obj.points) {
        point.x = xG + k * (point.x - xG);
        point.y = yG + k * (point.y - yG);
    }
}

// Scale a composed object (a vector of objects) by a factor of k
void scale_composedObject(std::vector<Object>& objects, double k) {
    for (auto& obj : objects) {
        scale_object(obj, k);
    }
}

void ListTransform::add(const std::string& type, double value) {
    Transform* newTransform = new Transform{type, value};
    newTransform->next = head;
    head = newTransform;
}

void ListTransform::remove(const std::string& type) {
    Transform* current = head;
    Transform* prev = nullptr;
    
    while (current != nullptr) {
        if (current->type == type) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void ListTransform::clear() {
    while (head != nullptr) {
        Transform* temp = head;
        head = head->next;
        delete temp;
    }
}

ListTransform::~ListTransform() {
    clear();
}

void apply_transform(Object& obj, const Transform& transform, Point center) {
    if (transform.type == "rotate") {
        double angle = transform.value * M_PI / 180.0;
        for (auto& point : obj.points) {
            double dx = point.x - center.x;
            double dy = point.y - center.y;
            point.x = center.x + dx * cos(angle) - dy * sin(angle);
            point.y = center.y + dx * sin(angle) + dy * cos(angle);
        }
    } else if (transform.type == "scale") {
        for (auto& point : obj.points) {
            point.x = center.x + (point.x - center.x) * transform.value;
            point.y = center.y + (point.y - center.y) * transform.value;
        }
    } else if (transform.type == "translate") {
        for (auto& point : obj.points) {
            point.x += transform.value;
            point.y += transform.value;
        }
    }
}

void apply_list_transform(Object& obj, const ListTransform& transforms, Point center) {
    Transform* current = transforms.head;
    while (current != nullptr) {
        apply_transform(obj, *current, center);
        current = current->next;
    }
}

void apply_random_transforms(Object& obj, const std::vector<Transform>& possible_transforms, Point center) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, possible_transforms.size());
    
    int num_transforms = dis(gen);
    for (int i = 0; i < num_transforms; ++i) {
        int transform_idx = dis(gen) % possible_transforms.size();
        apply_transform(obj, possible_transforms[transform_idx], center);
    }
}