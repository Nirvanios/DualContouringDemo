//
// Created by Igor Frank on 14.04.20.
//

#include <glm/glm.hpp>

#include "ThirdParty/Camera.h"
#include <Args.h>
#include <BaseDualContouring.h>
#include <DCWindow.h>
#include <Renderer.h>
#include <SimpleDualContouring.h>
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

  args.method = args.method.has_value() ? args.method.value() : MethodType::SIMPLE;

  auto dualContouring = BaseDualContouring::CreateInstance(args.method.value());
  if (args.method.value() == MethodType::SIMPLE) {
    dynamic_cast<SimpleDualContouring *>(dualContouring.get())->setDensity([](DualContouring::Vector3D pos) -> double {
      return VoxParser::getInstance().getRoot().Density(pos);
    });
  }

  dualContouring->computeMesh();

  renderer.fillBuffers(dualContouring->getVertices(), dualContouring->getIndices());

  window.setLoopCallback([&]() { renderer.drawFrame(); });

  window();
}