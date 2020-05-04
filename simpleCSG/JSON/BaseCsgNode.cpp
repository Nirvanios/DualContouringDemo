//
// Created by Igor Frank on 04.05.20.
//

#include "BaseCsgNode.h"
BaseCsgNode::BaseCsgNode(BaseCsgNode::NodeType nodeType) : nodeType(nodeType) {}
BaseCsgNode::NodeType BaseCsgNode::getNodeType() const { return nodeType; }
bool BaseCsgNode::isLeaf() {
  if (nodeType == NodeType::SHAPE)
    return true;
  else
    return false;
}
