//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_BASECSGNODE_H
#define DUALCONTOURDEMO_BASECSGNODE_H

#include <glm/glm.hpp>

class BaseCsgNode {

protected:
  enum class NodeType { OPERATION, SHAPE };

public:
  BaseCsgNode(NodeType nodeType);
  bool isLeaf();
  virtual double getDensity(const glm::vec3 &pos) = 0;

private:
  NodeType nodeType;

public:
  NodeType getNodeType() const;
};

#endif // DUALCONTOURDEMO_BASECSGNODE_H
