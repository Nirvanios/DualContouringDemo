//
// Created by Igor Frank on 26.04.20.
//

#include "MainChunk.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>
#include <operations.h>
#include <shapes.h>

double MainChunk::Density(const DualContouring::Vector3D &pos) const { return Density(glm::make_vec3(pos.data.data())); }

double MainChunk::Density(const glm::vec3 &pos) const {
  double result = std::numeric_limits<double>::max();
  std::vector<int> neighbours{-1, 0, 1};
  auto i = 0;
  for (const auto &model : this->models) {
    if (i == 0) {
      ++i;
      // continue;
    }
    for (const auto &z : neighbours) {
      for (const auto &y : neighbours) {
        for (const auto &x : neighbours) {
          result = Operations::Union(result, model.density(pos, pos + glm::vec3(x, y, z)));
        }
      }
    }
  }
  return result;
}
