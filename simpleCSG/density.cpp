#include "density.h"
#include <JSON/JsonLoader.h>
#include <glm/gtc/type_ptr.hpp>
#include <optional>
#include <vector3d.hh>
//
// Created by Igor Frank on 28.04.20.
//
double Density_FuncDC(const DualContouring::Vector3D &pos) { return Density_Func(glm::make_vec3(pos.data.data())); }
double Density_Func(const glm::vec3 &pos) {

  static std::optional<bool> isVoxModel;
  static std::optional<bool> isJsonFile;

  if (!isVoxModel.has_value()) {
    isVoxModel = VoxParser::getInstance().isFileLoaded();
  }
  if (!isJsonFile.has_value()) {
    isJsonFile = JsonLoader::getInstance().isJsonLoaded();
  }

  if (isVoxModel.value()) {
    return VoxParser::getInstance().getRoot().Density(pos);
  } else if (isJsonFile.value()) {
    // return Shapes::Cylinder(pos, glm::vec3(0), glm::vec3(10), Shapes::Axis::X);
    return JsonLoader::getInstance().getRoot()->getDensity(pos);
  } else
    return Shapes::Cuboid(pos, glm::vec3(0), glm::vec3(5));

  //    return Operations::Difference(Shapes::Cuboid(pos, glm::vec3(63), glm::vec3(20)),
  //                               Shapes::Sphere(pos, glm::vec3(72), 20));

  //    Operations::Union(Shapes::Cylinder(pos, glm::vec3(63, 0, 63), glm::vec3(10), Shapes::Axis::Y),
  //                             Operations::Union(Shapes::Cylinder(pos, glm::vec3(63, 63, 0), glm::vec3(10), Shapes::Axis::Z),
  //                                               Shapes::Cylinder(pos, glm::vec3(0, 63, 63), glm::vec3(10),
  //                                               Shapes::Axis::X))));
  //

  return Operations::Difference(Operations::Union(Shapes::Cylinder(pos, glm::vec3(63, 0, 63), glm::vec3(10), Shapes::Axis::Y),
                                                  Shapes::Cuboid(pos, glm::vec3(63), glm::vec3(20))),
                                Operations::Union(Shapes::Cylinder(pos, glm::vec3(63, 63, 0), glm::vec3(17), Shapes::Axis::Z),
                                                  Shapes::Cylinder(pos, glm::vec3(0, 63, 63), glm::vec3(17), Shapes::Axis::X)));

  return Shapes::Cone(pos, glm::vec3(0), glm::vec3(1));

  return Operations::Intersect(Shapes::Cone(pos, glm::vec3(0), glm::vec3(1)),
                               Shapes::Cuboid(pos, glm::vec3(0, 0, 5), glm::vec3(10, 10, 5)));

  return Shapes::Cuboid(pos, glm::vec3(0), glm::vec3(5));

  return Operations::Intersect(Shapes::Sphere(pos, glm::vec3(0), 5), Shapes::Sphere(pos, glm::vec3(2), 5));
}
