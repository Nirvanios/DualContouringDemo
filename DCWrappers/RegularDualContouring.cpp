//
// Created by Igor Frank on 30.04.20.
//

#include "RegularDualContouring.h"
#include <DualContouringSample/DualContouringSample/octree.h>
#include <VoxParser.h>
#include <glm/gtx/component_wise.hpp>
#include <limits>

void RegularDualContouring::computeMesh() {
  if (VoxParser::getInstance().isFileLoaded()) {
    auto max = glm::vec3(-std::numeric_limits<float>::max());
    auto min = glm::vec3(std::numeric_limits<float>::max());
    for (const auto &model : VoxParser::getInstance().getRoot().models) {
      auto c1 = model.getRotation() * model.getTranslation();
      auto c2 = model.getRotation() * (static_cast<glm::vec3>(model.getModelSize()) + model.getTranslation());
      max = glm::max(max, c1);
      max = glm::max(max, c2);
      min = glm::min(min, c1);
      min = glm::min(min, c2);
    }
    this->size = glm::uvec3(glm::abs(max - min)) + glm::uvec3(1);
    this->origin = min - 1.f;
  }

  auto sizeTo2 = pow(2, ceil(log(glm::compMax(this->size)) / log(2)));
  root = BuildOctree(glm::ivec3(origin), sizeTo2, 0.1f);
  GenerateMeshFromOctree(root, vb, ib);

  std::for_each(vb.begin(), vb.end(), [this](const MeshVertex &v) { vertices.emplace_back(v.xyz, v.normal); });
  indices.insert(indices.begin(), ib.begin(), ib.end());
}

RegularDualContouring::~RegularDualContouring() { DestroyOctree(root); }
RegularDualContouring::RegularDualContouring(const vec3 &origin, const vec3 &size) : BaseDualContouring(origin, size) {}
