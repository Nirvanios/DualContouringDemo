//
// Created by Igor Frank on 04.05.20.
//

#include "ElipsoidCsgShape.h"
#include <shapes.h>

double ElipsoidCsgShape::getDensity(const glm::vec3 &pos) { return Shapes::Elipsoid(pos, origin, constants); }
ElipsoidCsgShape::ElipsoidCsgShape(const glm::vec3 &origin, const glm::vec3 &constants)
    : BaseCsgShape(ShapeType::ELIPSOID, origin), constants(constants) {}
