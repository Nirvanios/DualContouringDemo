//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_RENDERER_H
#define DUALCONTOURDEMO_RENDERER_H

#include <geGL/geGL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Camera.h>
#include <VertexObject.h>

class Renderer {
  using GLprogram = std::shared_ptr<ge::gl::Program>;
  using GLBuffer = std::shared_ptr<ge::gl::Buffer>;
  using GLVertexArray = std::shared_ptr<ge::gl::VertexArray>;

public:
  Renderer(unsigned int windowWidth, unsigned int windowHeight, Camera &camera);
  void fillBuffers(const std::vector<VertexObject> &vertices, const std::vector<unsigned int> &indices);
  void fillVertexBuffer(const std::vector<VertexObject> &vertices);
  void fillIndexBuffer(const std::vector<unsigned int> &indices);
  void drawFrame();

private:
  unsigned int windowWidth;
  unsigned int windowHeight;

  Camera &camera;
  const float fieldOfView = 45.f;
  const float nearPlane = 0.1f;
  const float farPlane = 1000.f;
  const glm::mat4 modelMat = glm::mat4(1.0);
  glm::mat4 projectionMat;

  GLprogram program;
  GLBuffer vbo;
  GLBuffer ibo;
  GLVertexArray vao;
  unsigned int indicesSize;
};

#endif // DUALCONTOURDEMO_RENDERER_H
