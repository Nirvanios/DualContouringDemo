//
// Created by Igor Frank on 30.04.20.
//

#include "RegularDualContouring.h"
#include <DualContouringSample/DualContouringSample/octree.h>
#include <VoxParser.h>
#include <glm/gtx/component_wise.hpp>
#include <limits>

void RegularDualContouring::computeMesh() {
  if (VoxParser::getInstance().isFileLoaded()) {
    computeModelSize();
  }

  root = BuildOctree(glm::ivec3(origin), roundSizeToPower2(), -1.f);
  GenerateMeshFromOctree(root, vb, ib);

  std::for_each(vb.begin(), vb.end(), [this](const MeshVertex &v) { vertices.emplace_back(v.xyz, v.normal); });
  indices.insert(indices.begin(), ib.begin(), ib.end());
}

RegularDualContouring::~RegularDualContouring() { DestroyOctree(root); }
RegularDualContouring::RegularDualContouring(const vec3 &origin, const vec3 &size) : BaseDualContouring(origin, size) {}
void RegularDualContouring::setThreshold(float threshold) { RegularDualContouring::threshold = threshold; }
