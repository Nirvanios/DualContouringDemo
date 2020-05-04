//
// Created by Igor Frank on 14.04.20.
//

#include <glm/glm.hpp>

#include "ThirdParty/Camera.h"
#include <Args.h>
#include <BaseDualContouring.h>
#include <DCWindow.h>
#include <JSON/JsonLoader.h>
#include <Renderer.h>
#include <VoxParser.h>
#include <vector3d.hh>

#include "misc/Utils.h"

int main(int argc, char **argv) {
  auto args = Args();

  JsonLoader::getInstance().loadFile("../density.json");

  try {
    args.parseArgs(argc, argv);
  } catch (std::invalid_argument &e) {
    std::cout << e.what();
    std::cout << Args::getHelp();
    return (1);
  }

  if (args.inputFile.has_value()) {
    VoxParser::getInstance().loadFile(args.inputFile.value());
    for (auto &model : VoxParser::getInstance().getRoot().models) {
      model.buildOctree();
    }
  }

  args.method = args.method.has_value() ? args.method.value() : MethodType::REGULAR;

  auto dualContouring = BaseDualContouring::CreateInstance(args.method.value());

  dualContouring->computeMesh();

  if (args.outputFile.has_value()) {
    dualContouring->saveOBJfile(args.outputFile.value());
  }

  if (args.visualize) {
    auto camera = Camera(glm::vec3(0));

    /*Create Window*/
    auto window = DCWindow(camera);
    window.init();

    /*init OpenGL*/
    auto renderer = Renderer(window.getWidth(), window.getHeight(), camera);

    renderer.fillBuffers(dualContouring->getVertices(), dualContouring->getIndices());

    window.setLoopCallback([&]() { renderer.drawFrame(); });

    /*Render*/
    window();
  }
}