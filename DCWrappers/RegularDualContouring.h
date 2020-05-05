//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_REGULARDUALCONTOURING_H
#define DUALCONTOURDEMO_REGULARDUALCONTOURING_H

#include "BaseDualContouring.h"
#include <DualContouringSample/DualContouringSample/mesh.h>
#include <DualContouringSample/DualContouringSample/octree.h>
class RegularDualContouring : public BaseDualContouring {
public:
  RegularDualContouring(const vec3 &origin, const vec3 &size);

private:
  VertexBuffer vb{};
  IndexBuffer ib{};
  OctreeNode *root = nullptr;

  float threshold = 0.1;

public:
  virtual ~RegularDualContouring();
  void computeMesh() override;
  void setThreshold(float threshold);
};

#endif // DUALCONTOURDEMO_REGULARDUALCONTOURING_H
