//
// Created by Igor Frank on 04.05.20.
//

#include "CuboidCsgShape.h"
#include <shapes.h>
double CuboidCsgShape::getDensity(const glm::vec3 &pos) { return Shapes::Cuboid(pos, origin, halfDimensions); }
CuboidCsgShape::CuboidCsgShape(const glm::vec3 &origin, const glm::vec3 &halfDimensions)
    : BaseCsgShape(BaseCsgShape::ShapeType::CUBOID, origin), halfDimensions(halfDimensions) {}
