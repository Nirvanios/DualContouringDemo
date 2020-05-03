//
// Created by Igor Frank on 30.04.20.
//

#include "Args.h"
void Args::parseArgs(int argc, char **argv) {
  runPath = std::string(argv[0]);
  for (auto i = 1; i < argc; ++i) {
    std::string tmp = argv[i];
    if (tmp == "-h" || tmp == "--h") {
      help = true;
      break;
    }
    if (tmp == "-in") {
      if (inputFile.has_value())
        throw std::invalid_argument("Duplicate \"-in\" argument!");
      inputFile = argv[++i];
    } else if (tmp == "-out") {
      if (outputFile.has_value())
        throw std::invalid_argument("Duplicate \"-out\" argument!");
      outputFile = argv[++i];
    } else if (tmp == "-m=SIMPLE") {
      if (method.has_value())
        throw std::invalid_argument("Duplicate \"-m=XXX\" argument!");
      method = MethodType::SIMPLE;
    } else if (tmp == "-m=REGULAR") {
      if (method.has_value())
        throw std::invalid_argument("Duplicate \"-m=XXX\" argument!");
      method = MethodType::REGULAR;
    } else if (tmp == "-v") {
      visualize = true;
    } else {
      throw std::invalid_argument("Unknown argument " + std::string(argv[i]) + " !");
    }
  }
}
std::string Args::getHelp() {
  std::string help("TODO");
  return help;
}
