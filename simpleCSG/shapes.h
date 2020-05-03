//
// Created by Igor Frank on 15.04.20.
//

#ifndef DUALCONTOURDEMO_SHAPES_H
#define DUALCONTOURDEMO_SHAPES_H

#include <glm/glm.hpp>

namespace Shapes {
enum class Axis { X, Y, Z };

double Cuboid(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &halfDimensions);
double Sphere(const glm::vec3 &worldPosition, const glm::vec3 &origin, float radius);
double Elipsoid(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &constants);
double Cone(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &constants);
double Cylinder(const glm::vec3 &worldPosition, const glm::vec3 &origin, const glm::vec3 &constants, Axis parallelTo);
}

#endif // DUALCONTOURDEMO_SHAPES_H
