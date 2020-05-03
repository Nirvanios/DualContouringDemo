//
// Created by Igor Frank on 26.04.20.
//

#include "ModelChunk.h"
#include <NodeTree.h>
#include <array>
#include <glm/gtx/component_wise.hpp>

ModelChunk::ModelChunk(const glm::uvec3 &modelSize) : modelSize(modelSize) {}

const glm::uvec3 &ModelChunk::getModelSize() const { return modelSize; }

const std::vector<Voxel> &ModelChunk::getVoxels() const { return voxels; }

void ModelChunk::addVoxel(const glm::vec3 &position, const unsigned int &colorIndex) {
  this->voxels.emplace_back(position, colorIndex);
}

int cnt(const Node &nd) {
  auto sm = nd.full ? 1 : 0;
  for (const auto &n : nd.childs) {
    if (n != nullptr)
      sm += cnt(*n);
  }
  return sm;
}

void ModelChunk::buildOctree() {
  auto size = pow(2, ceil(log(glm::compMax(modelSize)) / log(2)));

  octreeRoot = Node(false, 32, glm::vec3(-16));

  for (const auto &voxel : voxels) {
    octreeRoot.addNode(voxel.pos);
  }
  // octreeRoot.simplify();
}

double ModelChunk::density(const glm::vec3 &worldPos, const glm::vec3 &searchPos) const {
  return octreeRoot.density(worldPos, searchPos);
}
const glm::mat3 &ModelChunk::getRotation() const { return rotation; }
void ModelChunk::setRotation(const glm::mat3 &rotation) { ModelChunk::rotation = rotation * ModelChunk::rotation; }
const glm::vec3 &ModelChunk::getTranslation() const { return translation; }
void ModelChunk::setTranslation(const glm::vec3 &translation) { ModelChunk::translation = translation + ModelChunk::translation; }
void ModelChunk::applyTransformation() {
  for (auto &voxel : voxels) {
    voxel.pos = rotation * (voxel.pos + translation);
  }
}
