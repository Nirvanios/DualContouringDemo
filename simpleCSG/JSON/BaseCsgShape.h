//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_BASECSGSHAPE_H
#define DUALCONTOURDEMO_BASECSGSHAPE_H

#include "BaseCsgNode.h"
#include <glm/glm.hpp>

class BaseCsgShape : public BaseCsgNode {

protected:
  glm::vec3 origin;

public:
  enum class ShapeType { UNKNOWN, CUBOID, SPHERE, ELIPSOID, CONE, CYLINDER };
  BaseCsgShape(ShapeType shapeType, const glm::vec3 &origin)
      : BaseCsgNode(NodeType::SHAPE), shapeType(shapeType), origin(origin) {}

private:
  ShapeType shapeType = ShapeType::UNKNOWN;
};

#endif // DUALCONTOURDEMO_BASECSGSHAPE_H
