//
// Created by Igor Frank on 26.04.20.
//

#ifndef DUALCONTOURDEMO_MODELCHUNK_H
#define DUALCONTOURDEMO_MODELCHUNK_H

#include "NodeTree.h"
#include <glm/glm.hpp>
#include <vector>

struct Voxel {
  glm::vec3 pos;
  unsigned int colorIndex;

  Voxel(const glm::vec3 &pos, unsigned int colorIndex) : pos(pos), colorIndex(colorIndex){};
};

class ModelChunk {

public:
  explicit ModelChunk(const glm::uvec3 &modelSize);

private:
  glm::uvec3 modelSize;

public:
  [[nodiscard]] const glm::uvec3 &getModelSize() const;
  [[nodiscard]] const std::vector<Voxel> &getVoxels() const;
  void addVoxel(const glm::vec3 &position, const unsigned int &colorIndex);
  void buildOctree();
  double density(const glm::vec3 &worldPos, const glm::vec3 &searchPos) const;

private:
  std::vector<Voxel> voxels;
  Node octreeRoot;
};

#endif // DUALCONTOURDEMO_MODELCHUNK_H
