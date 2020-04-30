//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_VERTEXOBJECT_H
#define DUALCONTOURDEMO_VERTEXOBJECT_H

#include <glm/glm.hpp>

class VertexObject {
public:
  VertexObject(const glm::vec3 &vertex, const glm::vec3 &normal = glm::vec3(0), const glm::vec3 &color = glm::vec3(0))
      : vertex(vertex), normal(normal), color(color) {}

  glm::vec3 color;
  glm::vec3 vertex;
  glm::vec3 normal;
};

#endif // DUALCONTOURDEMO_VERTEXOBJECT_H
