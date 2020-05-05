//
// Created by Igor Frank on 30.04.20.
//

#include <filesystem>
#include <iostream>

#include "Renderer.h"
#include <SDL2CPP/Window.h>
#include <Utils.h>
#include <geGL/StaticCalls.h>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer(unsigned int windowWidth, unsigned int windowHeight, Camera &camera)
    : windowWidth(windowWidth), windowHeight(windowHeight), camera(camera) {
  projectionMat =
      glm::perspective(glm::radians(fieldOfView), static_cast<float>(windowWidth) / windowHeight, nearPlane, farPlane);

  ge::gl::init(SDL_GL_GetProcAddress);
  ge::gl::setHighDebugMessage();

  auto vertexShaderFile = std::filesystem::current_path() / "shaders" / "simple.vert";
  auto fragmentShaderFile = std::filesystem::current_path() / "shaders" / "simple.frag";

  auto vs = std::make_shared<ge::gl::Shader>(GL_VERTEX_SHADER, Utils::readFile<std::string>(vertexShaderFile.string()));
  auto fs = std::make_shared<ge::gl::Shader>(GL_FRAGMENT_SHADER, Utils::readFile<std::string>(fragmentShaderFile.string()));
  program = std::make_shared<ge::gl::Program>(vs, fs);

  ge::gl::glClearColor(255, 255, 255, 1);
  ge::gl::glEnable(GL_DEPTH_TEST);
  // ge::gl::glEnable(GL_CULL_FACE);
  // ge::gl::glCullFace(GL_BACK);
}

void Renderer::fillVertexBuffer(const std::vector<VertexObject> &vertices) {
  vbo = std::make_shared<ge::gl::Buffer>(vertices.size() * sizeof(VertexObject), vertices.data());
  vao = std::make_shared<ge::gl::VertexArray>();
  vao->addAttrib(vbo, 0, 3, GL_FLOAT, static_cast<GLsizei>(sizeof(VertexObject)), offsetof(VertexObject, vertex));
  vao->addAttrib(vbo, 1, 3, GL_FLOAT, static_cast<GLsizei>(sizeof(VertexObject)), offsetof(VertexObject, normal));
}

void Renderer::fillIndexBuffer(const std::vector<unsigned int> &indices) {
  ibo = std::make_shared<ge::gl::Buffer>(indices.size() * sizeof(unsigned int), indices.data());
  indicesSize = indices.size();
}

void Renderer::fillBuffers(const std::vector<VertexObject> &vertices, const std::vector<unsigned int> &indices) {
  fillVertexBuffer(vertices);
  fillIndexBuffer(indices);
}

void Renderer::drawFrame() {
  ge::gl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  program->use();

  vao->bind();
  ibo->bind(GL_ELEMENT_ARRAY_BUFFER);

  const auto MVP = projectionMat * camera.GetViewMatrix() * modelMat;
  program->setMatrix4fv("MVP", glm::value_ptr(MVP));
  program->set3fv("camerPos", glm::value_ptr(camera.Position));

  ge::gl::glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, nullptr);

  vao->unbind();
  ibo->unbind(GL_ELEMENT_ARRAY_BUFFER);
}
