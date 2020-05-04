//
// Created by Igor Frank on 04.05.20.
//

#include "OperationCsgNode.h"
#include <operations.h>
double OperationCsgNode::getDensity(const glm::vec3 &pos) {
  switch (type) {

  case OperationType::UNKNOWN:
    throw std::runtime_error("UNKNOWN operation");
  case OperationType::UNION:
    return Operations::Union(op1->getDensity(pos), op2->getDensity(pos));
  case OperationType::DIFFERENCE:
    return Operations::Difference(op1->getDensity(pos), op2->getDensity(pos));
  case OperationType::INTERSECT:
    return Operations::Intersect(op1->getDensity(pos), op2->getDensity(pos));
  }
}
OperationCsgNode::OperationCsgNode(OperationCsgNode::OperationType type) : BaseCsgNode(NodeType::OPERATION), type(type) {}
void OperationCsgNode::setType(OperationCsgNode::OperationType type) { OperationCsgNode::type = type; }
