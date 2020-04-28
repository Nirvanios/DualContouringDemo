//
// Created by Igor Frank on 26.04.20.
//

#include "ModelChunk.h"

ModelChunk::ModelChunk(const glm::uvec3 &modelSize) : modelSize(modelSize) {}

const glm::uvec3 &ModelChunk::getModelSize() const { return modelSize; }

const std::vector<Voxel> &ModelChunk::getVoxels() const { return voxels; }

void ModelChunk::addVoxel(const glm::vec3 &position, const unsigned int &colorIndex) {
  this->voxels.emplace_back(position, colorIndex);
}
