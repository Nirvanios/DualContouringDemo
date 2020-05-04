//
// Created by Igor Frank on 04.05.20.
//

#include "ElipsoidCsgLeaf.h"
#include <shapes.h>

double ElipsoidCsgLeaf::getDensity(const glm::vec3 &pos) { return Shapes::Elipsoid(pos, origin, constants); }
ElipsoidCsgLeaf::ElipsoidCsgLeaf(const glm::vec3 &origin, const glm::vec3 &constants)
    : BaseCsgShape(ShapeType::ELIPSOID, origin), constants(constants) {}
