//
// Created by Igor Frank on 14.04.20.
//

#include <limits>

#include <SDL2CPP/Window.h>
#include <geGL/StaticCalls.h>
#include <geGL/geGL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ThirdParty/Camera.h"
#include "operations.h"
#include "shapes.h"
#include <VoxParser/VoxParser.h>
#include <dc.hh>
#include <geGL/StaticCalls.h>
#include <vector3d.hh>

#include "Utils.h"

Camera camera(glm::vec3(0));

std::pair<unsigned int, unsigned int> getWindowSize() {
  SDL_DisplayMode DM;
  if (SDL_GetDesktopDisplayMode(0, &DM) != 0) {
    throw std::runtime_error("SDL_GetDesktopDisplayMode failed");
  }
  const auto w = static_cast<unsigned int>(DM.w * 0.8);
  const auto h = static_cast<unsigned int>(DM.h * 0.8);
  return {w, h};
}

bool SDLHandler(const SDL_Event &event) {
  static bool mousePressed = false;
  if (event.type == SDL_KEYDOWN) {
    switch (event.key.keysym.sym) {
    case SDLK_UP:
    case SDLK_w:
      camera.ProcessKeyboard(Camera_Movement::FORWARD, 0.1);
      return true;
    case SDLK_DOWN:
    case SDLK_s:
      camera.ProcessKeyboard(Camera_Movement::BACKWARD, 0.1);
      return true;
    case SDLK_LEFT:
    case SDLK_a:
      camera.ProcessKeyboard(Camera_Movement::LEFT, 0.1);
      return true;
    case SDLK_RIGHT:
    case SDLK_d:
      camera.ProcessKeyboard(Camera_Movement::RIGHT, 0.1);
      return true;
    default:
      return false;
    }
  } else if (event.type == SDL_MOUSEBUTTONDOWN and
             event.button.button == SDL_BUTTON_LEFT) {
    mousePressed = true;
    return true;
  } else if (event.type == SDL_MOUSEMOTION and mousePressed) {
    camera.ProcessMouseMovement(-event.motion.xrel, event.motion.yrel);
    return true;
  } else if (event.type == SDL_MOUSEBUTTONUP and
             event.button.button == SDL_BUTTON_LEFT) {
    mousePressed = false;
    return true;
  }
  return false;
}

double Density(const DualContouring::Vector3D &pos) {

//    return Shapes::Cone(glm::make_vec3(pos.data.data()), glm::vec3(0), glm::vec3(1));

  return Operations::Intersect(
      Shapes::Cone(glm::make_vec3(pos.data.data()), glm::vec3(0), glm::vec3(1)),
      Shapes::Cuboid(glm::make_vec3(pos.data.data()), glm::vec3(0, 0, 5),
                     glm::vec3(10, 10, 5)));

    return Shapes::Cuboid(glm::make_vec3(pos.data.data()), glm::vec3(0),
                          glm::vec3(5));

  return Operations::Intersect(
      Shapes::Sphere(glm::make_vec3(pos.data.data()), glm::vec3(0), 5),
      Shapes::Sphere(glm::make_vec3(pos.data.data()), glm::vec3(2), 5));
}

struct VertexObject{
    glm::vec3 vertex;
    glm::vec3 normal;
    glm::vec3 color;
};

int main() {
  /*Create Window*/
  auto mainLoop = std::make_shared<sdl2cpp::MainLoop>();
  mainLoop->setEventHandler(SDLHandler);
  const auto fieldOfView = 45.f;
  const auto [windowWidth, windowHeight] = getWindowSize();
  const auto nearPlane = 0.1f;
  const auto farPlane = 100.f;
  const auto proj = glm::perspective(
      glm::radians(fieldOfView), static_cast<float>(windowWidth) / windowHeight,
      nearPlane, farPlane);
  const auto model = glm::mat4(1.0);

  auto window = std::make_shared<sdl2cpp::Window>(windowWidth, windowHeight);
  window->createContext("rendering");
  mainLoop->addWindow("mainWindow", window);

  /*init OpenGL*/
  ge::gl::init(SDL_GL_GetProcAddress);
  ge::gl::setHighDebugMessage();

  auto vs = std::make_shared<ge::gl::Shader>(
      GL_VERTEX_SHADER, Utils::readFile<std::string>("/home/kuro/CLionProjects/DualContouringDemo/shaders/simple.vert"));
  auto fs = std::make_shared<ge::gl::Shader>(
      GL_FRAGMENT_SHADER, Utils::readFile<std::string>("/home/kuro/CLionProjects/DualContouringDemo/shaders/simple.frag"));
  auto program = std::make_shared<ge::gl::Program>(vs, fs);

  /**
   * Compute Dual Contour
   */

  auto voxModel = VoxParser::parseFile("../vox/castle.vox");
  auto size = voxModel.models[0].getModelSize();

  auto mesh =
      DualContouring::isosurface([voxModel](auto &worldPos) { return voxModel.Density(worldPos); }, 0.0,
                                 std::array<DualContouring::Vector3D, 2>{DualContouring::Vector3D(-0.5, -0.5, -0.5),
                                                                         DualContouring::Vector3D(size.x, size.y, size.z)},
                                 std::array<size_t, 3>{64, 64, 64});

  mesh.writeOBJ("model.obj");

  std::vector<VertexObject> vertexObjects{};
  for(const auto &item : mesh.points){
    vertexObjects.emplace_back();
    auto &back = vertexObjects.back();
    back.vertex = glm::make_vec3(item.data.data());
  }

  std::vector<unsigned int> indices{};
  for (const auto &item : mesh.quads) {
    std::vector tmp(item.begin(), item.end());
    for (auto &i : tmp) {
      i -= 1;
    }
    indices.emplace_back(tmp[0]);
    indices.emplace_back(tmp[1]);
    indices.emplace_back(tmp[2]);
    auto norm = glm::cross(vertexObjects[tmp[1]].vertex - vertexObjects[tmp[0]].vertex,
                           vertexObjects[tmp[2]].vertex - vertexObjects[tmp[0]].vertex);
    vertexObjects[tmp[0]].normal += norm;
    vertexObjects[tmp[1]].normal += norm;
    vertexObjects[tmp[2]].normal += norm;
    indices.emplace_back(tmp[0]);
    indices.emplace_back(tmp[2]);
    indices.emplace_back(tmp[3]);
    norm = glm::cross(vertexObjects[tmp[2]].vertex - vertexObjects[tmp[0]].vertex,
                      vertexObjects[tmp[3]].vertex - vertexObjects[tmp[0]].vertex);
    vertexObjects[tmp[0]].normal += norm;
    vertexObjects[tmp[2]].normal += norm;
    vertexObjects[tmp[3]].normal += norm;
  }

  for(auto &vertexObject : vertexObjects){
    glm::normalize(vertexObject.normal);
  }


  auto vbo = std::make_shared<ge::gl::Buffer>(
      vertexObjects.size() * sizeof(VertexObject), vertexObjects.data());
  auto vao = std::make_shared<ge::gl::VertexArray>();
  vao->addAttrib(vbo, 0, 3, GL_FLOAT, static_cast<GLsizei>(sizeof(VertexObject)), offsetof(VertexObject, vertex));
  vao->addAttrib(vbo, 1, 3, GL_FLOAT, static_cast<GLsizei>(sizeof(VertexObject)), offsetof(VertexObject, normal));
  auto ibo = std::make_shared<ge::gl::Buffer>(
      indices.size() * sizeof(unsigned int), indices.data());

  ge::gl::glClearColor(255, 255, 255, 1);
  ge::gl::glEnable(GL_DEPTH_TEST);
//  ge::gl::glEnable(GL_CULL_FACE);
  ge::gl::glCullFace(GL_BACK);

  mainLoop->setIdleCallback([&]() {
    ge::gl::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program->use();

    vao->bind();
    ibo->bind(GL_ELEMENT_ARRAY_BUFFER);

    const auto MVP = proj * camera.GetViewMatrix() * model;
    program->setMatrix4fv("MVP", glm::value_ptr(MVP));
    program->set3fv("camerPos", glm::value_ptr(camera.Position));

    ge::gl::glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT,
                           nullptr);

    vao->unbind();
    ibo->unbind(GL_ELEMENT_ARRAY_BUFFER);

    window->swap();
  });

  (*mainLoop)();
}