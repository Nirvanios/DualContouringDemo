//
// Created by Igor Frank on 14.04.20.
//

#include <glm/glm.hpp>

#include "ThirdParty/Camera.h"
#include <Args.h>
#include <DCWindow.h>
#include <Renderer.h>
#include <VertexObject.h>
#include <VoxParser.h>
#include <dc.hh>
#include <vector3d.hh>

#include "ThirdParty/DualContouringSample/DualContouringSample/mesh.h"
#include "ThirdParty/DualContouringSample/DualContouringSample/octree.h"

#include "misc/Utils.h"

int main(int argc, char **argv) {
  auto args = Args();

  try {
    args.parseArgs(argc, argv);
  } catch (std::invalid_argument &e) {
    std::cout << e.what();
    std::cout << Args::getHelp();
    return (1);
  }

  auto camera = Camera(glm::vec3(0));

  /*Create Window*/
  auto window = DCWindow(camera);
  window.init();

  /*init OpenGL*/
  auto renderer = Renderer(window.getWidth(), window.getHeight(), camera);

  /**
   * Compute Dual Contour
   */

  VoxParser::getInstance().loadFile("../vox/castle.vox");
  VoxParser::getInstance().getRoot().models[0].buildOctree();

  VertexBuffer vb;
  IndexBuffer ib;

  auto root = BuildOctree(glm::ivec3(-1), 32, -1.f);
  GenerateMeshFromOctree(root, vb, ib);

  //  auto mesh =
  //      DualContouring::isosurface([voxModel](auto &worldPos) { return voxModel.Density(worldPos); }, 0.0,
  //                                 std::array<DualContouring::Vector3D, 2>{DualContouring::Vector3D(-0.5, -0.5, -0.5),
  //                                                                         DualContouring::Vector3D(size.x, size.y, size.z)},
  //                                 std::array<size_t, 3>{64, 64, 64});
  //
  //  mesh.writeOBJ("model.obj");
  //

  std::vector<VertexObject> vertexObjects{};
  std::vector<unsigned int> indices{};

  for (const auto vertex : vb) {
    vertexObjects.emplace_back(vertex.xyz, vertex.normal);
  }
  for (const auto index : ib) {
    indices.emplace_back(index);
  }

  //  for(const auto &item : mesh.points){
  //    vertexObjects.emplace_back();
  //    auto &back = vertexObjects.back();
  //    back.vertex = glm::make_vec3(item.data.data());
  //  }
  //

  //  for (const auto &item : mesh.quads) {
  //    std::vector tmp(item.begin(), item.end());
  //    for (auto &i : tmp) {
  //      i -= 1;
  //    }
  //    indices.emplace_back(tmp[0]);
  //    indices.emplace_back(tmp[1]);
  //    indices.emplace_back(tmp[2]);
  //    auto norm = glm::cross(vertexObjects[tmp[1]].vertex - vertexObjects[tmp[0]].vertex,
  //                           vertexObjects[tmp[2]].vertex - vertexObjects[tmp[0]].vertex);
  //    vertexObjects[tmp[0]].normal += norm;
  //    vertexObjects[tmp[1]].normal += norm;
  //    vertexObjects[tmp[2]].normal += norm;
  //    indices.emplace_back(tmp[0]);
  //    indices.emplace_back(tmp[2]);
  //    indices.emplace_back(tmp[3]);
  //    norm = glm::cross(vertexObjects[tmp[2]].vertex - vertexObjects[tmp[0]].vertex,
  //                      vertexObjects[tmp[3]].vertex - vertexObjects[tmp[0]].vertex);
  //    vertexObjects[tmp[0]].normal += norm;
  //    vertexObjects[tmp[2]].normal += norm;
  //    vertexObjects[tmp[3]].normal += norm;
  //  }
  //
  //  for(auto &vertexObject : vertexObjects){
  //    glm::normalize(vertexObject.normal);
  //  }

  renderer.fillBuffers(vertexObjects, indices);

  window.setLoopCallback([&]() { renderer.drawFrame(); });

  window();
}