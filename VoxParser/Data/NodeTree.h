//
// Created by Igor Frank on 28.04.20.
//

#ifndef DUALCONTOURDEMO_NODETREE_H
#define DUALCONTOURDEMO_NODETREE_H
#include <array>
#include <glm/glm.hpp>
#include <memory>

class Node {

public:
  Node(bool full = false, unsigned int size = 64, const glm::vec3 &position = glm::vec3(0))
      : full(full), size(size), position(position) {}

  enum class NodePosition {
    UNKNOWN = 0,
    FRONT = 1,
    BACK = 2,
    UP = 4,
    DOWN = 8,
    LEFT = 16,
    RIGHT = 32,
  };

public:
  std::array<std::unique_ptr<Node>, 8> childs;
  bool full = false;
  unsigned int size;
  glm::vec3 position;

  void addNode(const glm::vec3 &addedPos);
  bool simplify();

  [[nodiscard]] double density(const glm::vec3 &worldPos, const glm::vec3 &searchPos) const;

  static int enum2index(NodePosition pos);
  [[nodiscard]] int getIndex(const glm::vec3 &addedPos) const;
};
#endif // DUALCONTOURDEMO_NODETREE_H
