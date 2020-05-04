//
// Created by Igor Frank on 30.04.20.
//

#include "SimpleDualContouring.h"
#include <dc.hh>
#include <density.h>
#include <glm/gtc/type_ptr.hpp>
void SimpleDualContouring::computeMesh() {
  // TODO get whole size
  auto mesh = DualContouring::isosurface(
      Density_FuncDC, 0.0,
      std::array<DualContouring::Vector3D, 2>{DualContouring::Vector3D(-0.5, -0.5, -0.5), DualContouring::Vector3D(32, 32, 32)},
      std::array<size_t, 3>{64, 64, 64});

  for (const auto &item : mesh.points) {
    vertices.emplace_back(glm::make_vec3(item.data.data()));
  }

  for (const auto &item : mesh.quads) {
    std::vector tmp(item.begin(), item.end());
    for (auto &i : tmp) {
      i -= 1;
    }
    indices.emplace_back(tmp[0]);
    indices.emplace_back(tmp[1]);
    indices.emplace_back(tmp[2]);
    auto norm = glm::cross(vertices[tmp[1]].vertex - vertices[tmp[0]].vertex, vertices[tmp[2]].vertex - vertices[tmp[0]].vertex);
    vertices[tmp[0]].normal += norm;
    vertices[tmp[1]].normal += norm;
    vertices[tmp[2]].normal += norm;
    indices.emplace_back(tmp[0]);
    indices.emplace_back(tmp[2]);
    indices.emplace_back(tmp[3]);
    norm = glm::cross(vertices[tmp[2]].vertex - vertices[tmp[0]].vertex, vertices[tmp[3]].vertex - vertices[tmp[0]].vertex);
    vertices[tmp[0]].normal += norm;
    vertices[tmp[2]].normal += norm;
    vertices[tmp[3]].normal += norm;
  }

  for (auto &vertexObject : vertices) {
    glm::normalize(vertexObject.normal);
  }
}
SimpleDualContouring::SimpleDualContouring(const glm::vec3 &origin, const glm::vec3 &size) : BaseDualContouring(origin, size) {}
