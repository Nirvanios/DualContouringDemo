//
// Created by Igor Frank on 04.05.20.
//

#include "CuboidCsgLeaf.h"
#include <shapes.h>
double CuboidCsgLeaf::getDensity(const glm::vec3 &pos) { return Shapes::Cuboid(pos, origin, halfDimensions); }
CuboidCsgLeaf::CuboidCsgLeaf(const glm::vec3 &origin, const glm::vec3 &halfDimensions)
    : BaseCsgShape(BaseCsgShape::ShapeType::CUBOID, origin), halfDimensions(halfDimensions) {}
