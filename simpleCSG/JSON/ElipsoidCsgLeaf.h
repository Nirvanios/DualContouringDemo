//
// Created by Igor Frank on 04.05.20.
//

#ifndef DUALCONTOURDEMO_ELIPSOIDCSGLEAF_H
#define DUALCONTOURDEMO_ELIPSOIDCSGLEAF_H

#include "BaseCsgShape.h"
class ElipsoidCsgLeaf : public BaseCsgShape {
public:
  ElipsoidCsgLeaf(const glm::vec3 &origin, const glm::vec3 &constants);

public:
  double getDensity(const glm::vec3 &pos) override;
  glm::vec3 constants;
};

#endif // DUALCONTOURDEMO_ELIPSOIDCSGLEAF_H
