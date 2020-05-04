//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_ARGS_H
#define DUALCONTOURDEMO_ARGS_H

#include <MethodType.h>
#include <filesystem>
#include <optional>
#include <string>

#include <glm/glm.hpp>

class Args {
public:
  std::string runPath;
  std::optional<MethodType> method;
  std::optional<std::filesystem::path> inputFile;
  std::optional<std::filesystem::path> outputFile;
  glm::vec3 origin{-32};
  glm::vec3 size{64};
  bool visualize = false;
  bool help = false;

  Args() = default;
  void parseArgs(int argc, char **argv);
  static std::string getHelp();
};

#endif // DUALCONTOURDEMO_ARGS_H
