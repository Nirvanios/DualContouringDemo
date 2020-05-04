//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_CONECSGSHAPE_H
#define DUALCONTOURDEMO_CONECSGSHAPE_H

#include "BaseCsgShape.h"
class ConeCsgShape : public BaseCsgShape {
public:
  ConeCsgShape(const glm::vec3 &origin, const glm::vec3 &constants);

public:
  double getDensity(const glm::vec3 &pos) override;
  const glm::vec3 &constants;
};

#endif // DUALCONTOURDEMO_CONECSGSHAPE_H
