//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_ELIPSOIDCSGSHAPE_H
#define DUALCONTOURDEMO_ELIPSOIDCSGSHAPE_H

#include "BaseCsgShape.h"
class ElipsoidCsgShape : public BaseCsgShape {
public:
  ElipsoidCsgShape(const glm::vec3 &origin, const glm::vec3 &constants);

public:
  double getDensity(const glm::vec3 &pos) override;
  glm::vec3 constants;
};

#endif // DUALCONTOURDEMO_ELIPSOIDCSGSHAPE_H
