//
// Created by Igor Frank on 26.04.20.
//

#include "MainChunk.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <operations.h>
#include <shapes.h>

double MainChunk::Density(const DualContouring::Vector3D &pos) const {
  double result = std::numeric_limits<double>::max();
  for (const auto &model : this->models) {
    for (const auto &voxel : model.getVoxels()) {
      result = Operations::Union(result, Shapes::Cuboid(glm::make_vec3(pos.data.data()), voxel.pos, glm::vec3(0.5)));
    }
  }
  return result;
}
