//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_BASEDUALCONTOURING_H
#define DUALCONTOURDEMO_BASEDUALCONTOURING_H

#include "MethodType.h"
#include <VertexObject.h>
#include <memory>
#include <string>
#include <vector>
class BaseDualContouring {
protected:
  std::vector<VertexObject> vertices;
  std::vector<unsigned int> indices;
  glm::vec3 origin;
  glm::vec3 size;

public:
  [[nodiscard]] const std::vector<VertexObject> &getVertices() const;
  [[nodiscard]] const std::vector<unsigned int> &getIndices() const;

public:
  BaseDualContouring(const glm::vec3 &origin, const glm::vec3 &size);

  virtual void computeMesh() = 0;
  void saveOBJfile(const std::string &path);

  static std::unique_ptr<BaseDualContouring> CreateInstance(MethodType type, const glm::vec3 &origin, const glm::vec3 &size);
};

#endif // DUALCONTOURDEMO_BASEDUALCONTOURING_H
