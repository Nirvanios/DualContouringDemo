//
// Created by Igor Frank on 04.05.20.
//

#include "ConeCsgShape.h"
#include <shapes.h>
double ConeCsgShape::getDensity(const glm::vec3 &pos) { return Shapes::Cone(pos, origin, constants); }
ConeCsgShape::ConeCsgShape(const glm::vec3 &origin, const glm::vec3 &constants)
    : BaseCsgShape(BaseCsgShape::ShapeType::CONE, origin), constants(constants) {}
