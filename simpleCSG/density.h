//
// Created by Igor Frank on 28.04.20.
//

#ifndef DUALCONTOURDEMO_DENSITY_H
#define DUALCONTOURDEMO_DENSITY_H

#include "operations.h"
#include "shapes.h"
#include <VoxParser.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector3d.hh>

double Density_Func(const glm::vec3 &pos) {

  return VoxParser::getInstance().getRoot().Density(pos);

  //    return Shapes::Cone(glm::make_vec3(pos.data.data()), glm::vec3(0), glm::vec3(1));

  return Operations::Intersect(Shapes::Cone(pos, glm::vec3(0), glm::vec3(1)),
                               Shapes::Cuboid(pos, glm::vec3(0, 0, 5), glm::vec3(10, 10, 5)));

  return Shapes::Cuboid(pos, glm::vec3(0), glm::vec3(5));

  return Operations::Intersect(Shapes::Sphere(pos, glm::vec3(0), 5), Shapes::Sphere(pos, glm::vec3(2), 5));
}

double Density_Func(const DualContouring::Vector3D &pos) { Density_Func(glm::make_vec3(pos.data.data())); }

#endif // DUALCONTOURDEMO_DENSITY_H
