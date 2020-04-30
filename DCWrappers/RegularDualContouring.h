//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_REGULARDUALCONTOURING_H
#define DUALCONTOURDEMO_REGULARDUALCONTOURING_H

#include "BaseDualContouring.h"
#include <DualContouringSample/DualContouringSample/mesh.h>
#include <DualContouringSample/DualContouringSample/octree.h>
class RegularDualContouring : public BaseDualContouring {
private:
  VertexBuffer vb;
  IndexBuffer ib;
  OctreeNode *root;

public:
  virtual ~RegularDualContouring();
  void computeMesh() override;
};

#endif // DUALCONTOURDEMO_REGULARDUALCONTOURING_H
