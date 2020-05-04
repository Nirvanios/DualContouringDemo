//
// Created by Igor Frank on 04.05.20.
//

#include "SphereCsgShape.h"
#include <shapes.h>
double SphereCsgShape::getDensity(const glm::vec3 &pos) { return Shapes::Sphere(pos, origin, radius); }
SphereCsgShape::SphereCsgShape(const glm::vec3 &origin, float radius)
    : BaseCsgShape(SphereCsgShape::ShapeType::SPHERE, origin), radius(radius) {}
