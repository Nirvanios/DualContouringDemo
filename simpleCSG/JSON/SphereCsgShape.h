//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_SPHERECSGSHAPE_H
#define DUALCONTOURDEMO_SPHERECSGSHAPE_H

#include "BaseCsgShape.h"
class SphereCsgShape : public BaseCsgShape {
public:
  explicit SphereCsgShape(const glm::vec3 &origin, float radius);

public:
  double getDensity(const glm::vec3 &pos) override;

private:
  float radius;
};

#endif // DUALCONTOURDEMO_SPHERECSGSHAPE_H
