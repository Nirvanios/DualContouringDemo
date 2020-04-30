//
// Created by Igor Frank on 28.04.20.
//

#include <NodeTree.h>
#include <operations.h>
#include <shapes.h>

inline Node::NodePosition operator|(Node::NodePosition l, Node::NodePosition r) {
  using T = std::underlying_type_t<Node::NodePosition>;
  return static_cast<Node::NodePosition>(static_cast<T>(l) | static_cast<T>(r));
}

inline Node::NodePosition operator&(Node::NodePosition l, Node::NodePosition r) {
  using T = std::underlying_type_t<Node::NodePosition>;
  return static_cast<Node::NodePosition>(static_cast<T>(l) & static_cast<T>(r));
}

inline Node::NodePosition &operator|=(Node::NodePosition &l, Node::NodePosition r) {
  l = l | r;
  return l;
}

int Node::enum2index(NodePosition pos) {
  using T = std::underlying_type_t<NodePosition>;
  if (pos == (NodePosition::FRONT | NodePosition::UP | NodePosition::LEFT)) {
    return 0;
  }
  if (pos == (NodePosition::FRONT | NodePosition::UP | NodePosition::RIGHT)) {
    return 1;
  }
  if (pos == (NodePosition::FRONT | NodePosition::DOWN | NodePosition::LEFT)) {
    return 2;
  }
  if (pos == (NodePosition::FRONT | NodePosition::DOWN | NodePosition::RIGHT)) {
    return 3;
  }
  if (pos == (NodePosition::BACK | NodePosition::UP | NodePosition::LEFT)) {
    return 4;
  }
  if (pos == (NodePosition::BACK | NodePosition::UP | NodePosition::RIGHT)) {
    return 5;
  }
  if (pos == (NodePosition::BACK | NodePosition::DOWN | NodePosition::LEFT)) {
    return 6;
  }
  if (pos == (NodePosition::BACK | NodePosition::DOWN | NodePosition::RIGHT)) {
    return 7;
  }
}

int Node::getIndex(const glm::vec3 &addedPos) const {
  auto index = NodePosition::UNKNOWN;
  auto childSize = size / 2;
  if (addedPos.z >= childSize + position.z)
    index |= NodePosition::FRONT;
  else
    index |= NodePosition::BACK;
  if (addedPos.y >= childSize + position.y)
    index |= NodePosition::UP;
  else
    index |= NodePosition::DOWN;
  if (addedPos.x >= childSize + position.x)
    index |= NodePosition::RIGHT;
  else
    index |= NodePosition::LEFT;

  return enum2index(index);
}

void Node::addNode(const glm::vec3 &addedPos) {
  if (size == 1) {
    full = true;
    return;
  } else {
    auto childSize = size / 2;
    auto index = getIndex(addedPos);
    auto childPos = position + glm::vec3(glm::greaterThanEqual(addedPos, position + glm::vec3(childSize))) * glm::vec3(childSize);
    if (childs[index] == nullptr) {
      childs[index] = std::make_unique<Node>(false, childSize, childPos);
    }
    childs[index]->addNode(addedPos);
  }
}
bool Node::simplify() {
  if (full)
    return true;
  auto isFull = true;
  for (auto &node : childs) {
    if (node == nullptr) {
      isFull = false;
      continue;
    }
    isFull *= node->simplify();
  }
  if (isFull) {
    full = true;
    for (auto &node : childs) {
      node = nullptr;
    }
  }
  return isFull;
}

double Node::density(const glm::vec3 &worldPos, const glm::vec3 &searchPos) const {
  if (full)
    return Shapes::Cuboid(worldPos, position, glm::vec3(size / 2.));
  //  double result = std::numeric_limits<double>::max();
  //  for(const auto &child : childs){
  //    if(child != nullptr)
  //      result = Operations::Union(result, child->density(worldPos));
  //  }
  auto index = getIndex(searchPos);
  if (childs[index] != nullptr)
    return childs[index]->density(worldPos, searchPos);
  else
    return std::numeric_limits<double>::max();
}
