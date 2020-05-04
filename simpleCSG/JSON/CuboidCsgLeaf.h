//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_CUBOIDCSGLEAF_H
#define DUALCONTOURDEMO_CUBOIDCSGLEAF_H

#include "BaseCsgShape.h"
class CuboidCsgLeaf : public BaseCsgShape {
public:
  CuboidCsgLeaf(const glm::vec3 &origin, const glm::vec3 &halfDimensions);
  double getDensity(const glm::vec3 &pos) override;

private:
  glm::vec3 halfDimensions;
};

#endif // DUALCONTOURDEMO_CUBOIDCSGLEAF_H
