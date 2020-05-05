//
// Created by Igor Frank on 14.04.20.
//

#include <glm/glm.hpp>

#include "ThirdParty/Camera.h"
#include <Args.h>
#include <BaseDualContouring.h>
#include <DCWindow.h>
#include <JSON/JsonLoader.h>
#include <RegularDualContouring.h>
#include <Renderer.h>
#include <VoxParser.h>
#include <vector3d.hh>

#include "misc/Utils.h"

int main(int argc, char **argv) {
  auto args = Args();

  try {
    args.parseArgs(argc, argv);
  } catch (std::invalid_argument &e) {
    if (std::string(e.what()) == "stof") {
      std::cerr << "Bad numerical value in args." << std::endl;
    } else {
      std::cerr << e.what() << std::endl;
    }
    std::cout << Args::getHelp();
    return 1;
  }

  if (args.help) {
    std::cout << Args::getHelp();
    return 0;
  }

  try {
    if (args.inputFile.has_value()) {
      if (args.inputFile->extension() == ".vox") {
        VoxParser::getInstance().loadFile(args.inputFile.value());
        for (auto &model : VoxParser::getInstance().getRoot().models) {
          model.buildOctree();
        }
      } else if (args.inputFile->extension() == ".json") {
        JsonLoader::getInstance().loadFile(args.inputFile.value());
      } else
        throw std::runtime_error("Unknown file extension, expected .json or .vox got " + args.inputFile->extension().string());
    }
  } catch (std::exception &e) {
    std::cerr << e.what();
    return 1;
  }

  args.method = args.method.has_value() ? args.method.value() : MethodType::REGULAR;

  auto dualContouring = BaseDualContouring::CreateInstance(args.method.value(), args.origin, args.size);

  if (args.threshold.has_value() && args.method == MethodType::REGULAR) {
    dynamic_cast<RegularDualContouring *>(dualContouring.get())->setThreshold(args.threshold.value());
  }

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