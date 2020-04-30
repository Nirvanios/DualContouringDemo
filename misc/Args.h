//
// Created by Igor Frank on 30.04.20.
//

#ifndef DUALCONTOURDEMO_ARGS_H
#define DUALCONTOURDEMO_ARGS_H

#include <MethodType.h>
#include <optional>
#include <string>

class Args {
public:
  std::string runPath;
  std::optional<MethodType> method;
  std::optional<std::string> inputFile;
  std::optional<std::string> outputFile;
  bool visualize = false;
  bool help = false;

  Args() = default;
  void parseArgs(int argc, char **argv);
  static std::string getHelp();
};

#endif // DUALCONTOURDEMO_ARGS_H
