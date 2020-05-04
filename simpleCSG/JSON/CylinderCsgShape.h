//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_CYLINDERCSGSHAPE_H
#define DUALCONTOURDEMO_CYLINDERCSGSHAPE_H

#include "BaseCsgShape.h"
#include <shapes.h>
class CylinderCsgShape : public BaseCsgShape {
public:
  CylinderCsgShape(const glm::vec3 &origin, const glm::vec3 &constants, Shapes::Axis parallelTo);

public:
  double getDensity(const glm::vec3 &pos) override;
  const glm::vec3 &constants;
  Shapes::Axis parallelTo;
};

#endif // DUALCONTOURDEMO_CYLINDERCSGSHAPE_H
