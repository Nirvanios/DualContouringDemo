//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_OPERATIONCSGNODE_H
#define DUALCONTOURDEMO_OPERATIONCSGNODE_H

#include "BaseCsgNode.h"
#include "BaseCsgShape.h"
#include <memory>
class OperationCsgNode : public BaseCsgNode {

public:
  enum class OperationType { UNKNOWN, UNION, DIFFERENCE, INTERSECT };

  explicit OperationCsgNode(OperationType type);

  double getDensity(const glm::vec3 &pos) override;

private:
  OperationType type = OperationType::UNKNOWN;

public:
  void setType(OperationType type);
  std::shared_ptr<BaseCsgNode> op1 = nullptr;
  std::shared_ptr<BaseCsgNode> op2 = nullptr;
};

#endif // DUALCONTOURDEMO_OPERATIONCSGNODE_H
