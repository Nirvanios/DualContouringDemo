//
// Created by Igor Frank on 30.04.20.
//

#include "BaseDualContouring.h"
#include "RegularDualContouring.h"
#include "SimpleDualContouring.h"
#include <fstream>
#include <glm/gtx/string_cast.hpp>
#include <sstream>

BaseDualContouring::BaseDualContouring() {}
const std::vector<VertexObject> &BaseDualContouring::getVertices() const { return vertices; }
const std::vector<unsigned int> &BaseDualContouring::getIndices() const { return indices; }
void BaseDualContouring::saveOBJfile(const std::string &path) {
  std::stringstream objVertices;
  // std::string objNormals;
  std::stringstream objIndices;
  std::ofstream file(path);

  auto indexSize = indices.size();
  for (const auto &vertex : vertices) {
    objVertices << "v " << glm::to_string(vertex.vertex) << std::endl;
  }
  for (auto i = 0; i < indexSize; i += 3) {
    objIndices << "i " << indices[i] << ' ' << indices[i + 1] << ' ' << indices[i + 2] << ' ' << std::endl;
  }
  file << objVertices.rdbuf() << objIndices.rdbuf();
}
std::unique_ptr<BaseDualContouring> BaseDualContouring::CreateInstance(MethodType type) {
  switch (type) {
  case MethodType::SIMPLE:
    return std::make_unique<SimpleDualContouring>();
  case MethodType::REGULAR:
    return std::make_unique<RegularDualContouring>();
  }
}
