//
// Created by Igor Frank on 03.05.20.
//

#ifndef DUALCONTOURDEMO_TRANSFORMATIONTREE_H
#define DUALCONTOURDEMO_TRANSFORMATIONTREE_H

#include <glm/glm.hpp>
#include <vector>

class TransformationTree {
public:
  enum class TransformNodeType { UNKNOWN, TRANSFORM, GROUP, SHAPE };

  int nodeId = 0;
  TransformNodeType type = TransformNodeType::UNKNOWN;
  glm::mat3 rotation = glm::mat3(1.0);
  glm::vec3 translation = glm::vec3(0);
  std::vector<int> childIds{};
};

#endif // DUALCONTOURDEMO_TRANSFORMATIONTREE_H
