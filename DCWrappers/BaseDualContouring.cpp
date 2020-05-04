//
// Created by Igor Frank on 30.04.20.
//

#include "BaseDualContouring.h"
#include "RegularDualContouring.h"
#include "SimpleDualContouring.h"
#include <Utils.h>
#include <VoxParser.h>
#include <fstream>
#include <glm/gtx/component_wise.hpp>
#include <glm/gtx/string_cast.hpp>
#include <sstream>

BaseDualContouring::BaseDualContouring(const glm::vec3 &origin, const glm::vec3 &size) : origin(origin), size(size) {}
const std::vector<VertexObject> &BaseDualContouring::getVertices() const { return vertices; }
const std::vector<unsigned int> &BaseDualContouring::getIndices() const { return indices; }
void BaseDualContouring::saveOBJfile(const std::string &path) {
  std::stringstream objVertices;
  // std::string objNormals;
  std::stringstream objIndices;
  std::ofstream file(path);

  auto indexSize = indices.size();
  for (const auto &vertex : vertices) {
    objVertices << "v " << vertex.vertex.x << ' ' << vertex.vertex.y << ' ' << vertex.vertex.z << std::endl;
  }
  for (auto i = 0; i < indexSize; i += 3) {
    objIndices << "f " << indices[i] + 1 << ' ' << indices[i + 1] + 1 << ' ' << indices[i + 2] + 1 << ' ' << std::endl;
  }
  file << objVertices.rdbuf() << objIndices.rdbuf();
}
std::unique_ptr<BaseDualContouring> BaseDualContouring::CreateInstance(MethodType type, const glm::vec3 &origin,
                                                                       const glm::vec3 &size) {
  switch (type) {
  case MethodType::SIMPLE:
    return std::make_unique<SimpleDualContouring>(origin, size);
  case MethodType::REGULAR:
    return std::make_unique<RegularDualContouring>(origin, size);
  }
}
void BaseDualContouring::computeModelSize() {
  auto max = glm::vec3(-std::numeric_limits<float>::max());
  auto min = glm::vec3(std::numeric_limits<float>::max());
  for (const auto &model : VoxParser::getInstance().getRoot().models) {
    auto c1 = model.getRotation() * model.getTranslation();
    auto c2 = model.getRotation() * (static_cast<glm::vec3>(model.getModelSize()) + model.getTranslation());
    max = glm::max(max, c1);
    max = glm::max(max, c2);
    min = glm::min(min, c1);
    min = glm::min(min, c2);
  }
  this->size = glm::uvec3(glm::abs(max - min)) + glm::uvec3(1);
  this->origin = min - 1.f;
}
int BaseDualContouring::roundSizeToPower2() { return pow(2, ceil(log(glm::compMax(this->size)) / log(2))); }
