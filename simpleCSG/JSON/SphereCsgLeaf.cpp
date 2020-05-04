//
// Created by Igor Frank on 04.05.20.
//

#include "SphereCsgLeaf.h"
#include <shapes.h>
double SphereCsgLeaf::getDensity(const glm::vec3 &pos) { return Shapes::Sphere(pos, origin, radius); }
SphereCsgLeaf::SphereCsgLeaf(ShapeType shapeType, const glm::vec3 &origin, float radius)
    : BaseCsgShape(shapeType, origin), radius(radius) {}
