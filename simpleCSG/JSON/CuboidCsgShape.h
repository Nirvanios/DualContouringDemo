//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_CUBOIDCSGSHAPE_H
#define DUALCONTOURDEMO_CUBOIDCSGSHAPE_H

#include "BaseCsgShape.h"
class CuboidCsgShape : public BaseCsgShape {
public:
  CuboidCsgShape(const glm::vec3 &origin, const glm::vec3 &halfDimensions);
  double getDensity(const glm::vec3 &pos) override;

private:
  glm::vec3 halfDimensions;
};

#endif // DUALCONTOURDEMO_CUBOIDCSGSHAPE_H
