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
  glm::mat3 rotation = glm::mat3(1.0);

public:
  const glm::mat3 &getRotation() const;
  void setRotation(const glm::mat3 &rotation);
  const glm::vec3 &getTranslation() const;
  void setTranslation(const glm::vec3 &translation);

private:
  glm::vec3 translation = glm::vec3(0);

public:
  [[nodiscard]] const glm::uvec3 &getModelSize() const;
  [[nodiscard]] const std::vector<Voxel> &getVoxels() const;
  void addVoxel(const glm::vec3 &position, const unsigned int &colorIndex);
  void buildOctree(const glm::vec3 &origin, const glm::vec3 &size);
  void applyTransformation();
  double density(const glm::vec3 &worldPos, const glm::vec3 &searchPos) const;

private:
  std::vector<Voxel> voxels;
  Node octreeRoot;
};

#endif // DUALCONTOURDEMO_MODELCHUNK_H
