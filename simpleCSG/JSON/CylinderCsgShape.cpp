//
// Created by Igor Frank on 04.05.20.
//

#include "CylinderCsgShape.h"
#include <shapes.h>
double CylinderCsgShape::getDensity(const glm::vec3 &pos) { return Shapes::Cylinder(pos, origin, constants, parallelTo); }
CylinderCsgShape::CylinderCsgShape(const glm::vec3 &origin, const glm::vec3 &constants, Shapes::Axis parallelTo)
    : BaseCsgShape(BaseCsgShape::ShapeType::CYLINDER, origin), constants(constants), parallelTo(parallelTo) {}
