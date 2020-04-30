//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_SIMPLEDUALCONTOURING_H
#define DUALCONTOURDEMO_SIMPLEDUALCONTOURING_H

#include "BaseDualContouring.h"
#include <Data/MainChunk.h>
#include <functional>

class SimpleDualContouring : public BaseDualContouring {
private:
  std::function<double(const DualContouring::Point3D &)> density;

public:
  void setDensity(const std::function<double(const DualContouring::Point3D &)> &density);

public:
  void computeMesh() override;
};

#endif // DUALCONTOURDEMO_SIMPLEDUALCONTOURING_H
