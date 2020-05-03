//
// Created by Igor Frank on 14.04.20.
//

#include <glm/glm.hpp>
#include <glm/gtx/component_wise.hpp>

#include "shapes.h"

namespace Shapes {
double Cuboid(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &halfDimensions) {
  const auto &pos = worldPosition - origin;

  const auto &d = glm::abs(pos) - halfDimensions;
  const float m = glm::compMax(d);
  return glm::min(m, glm::length(glm::max(d, glm::vec3(0.f))));
}

double Sphere(const glm::vec3 &worldPosition, const glm::vec3 &origin, float radius) {
  return glm::length(worldPosition - origin) - radius;
}

double Elipsoid(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &constants) {
  const auto &pos = worldPosition - origin;

  return glm::compAdd(glm::pow(pos, glm::vec3(2)) / glm::pow(constants, glm::vec3(2))) - 1;
}

double Cone(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &constants) {
  const auto &pos = worldPosition - origin;

  const auto inter = glm::pow(pos, glm::vec3(2)) / glm::pow(constants, glm::vec3(2));

  return inter.x + inter.y - inter.z;
}
double Cylinder(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &constants, Axis parallelTo) {
  auto pos = worldPosition;
  switch (parallelTo) {
  case Axis::X:
    pos.x = 0;
    break;
  case Axis::Y:
    pos.y = 0;
    break;
  case Axis::Z:
    pos.z = 0;
    break;
  }
  return Elipsoid(pos, origin, constants);
}
} // namespace Shapes