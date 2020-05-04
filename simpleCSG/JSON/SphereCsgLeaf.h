//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_SPHERECSGLEAF_H
#define DUALCONTOURDEMO_SPHERECSGLEAF_H

#include "BaseCsgShape.h"
class SphereCsgLeaf : public BaseCsgShape {
public:
  explicit SphereCsgLeaf(const glm::vec3 &origin, float radius);

public:
  double getDensity(const glm::vec3 &pos) override;

private:
  float radius;
};

#endif // DUALCONTOURDEMO_SPHERECSGLEAF_H
