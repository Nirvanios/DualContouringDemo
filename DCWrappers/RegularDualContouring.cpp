//
// Created by Igor Frank on 30.04.20.
//

#include "RegularDualContouring.h"
#include <DualContouringSample/DualContouringSample/octree.h>

void RegularDualContouring::computeMesh() {
  root = BuildOctree(glm::ivec3(-17), 32, 0.1f);
  GenerateMeshFromOctree(root, vb, ib);

  std::for_each(vb.begin(), vb.end(), [this](const MeshVertex &v) { vertices.emplace_back(v.xyz, v.normal); });
  indices.insert(indices.begin(), ib.begin(), ib.end());
}

RegularDualContouring::~RegularDualContouring() { DestroyOctree(root); }
